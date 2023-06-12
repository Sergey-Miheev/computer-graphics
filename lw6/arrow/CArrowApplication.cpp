#define GLEW_STATIC
#include "glew.h"
#include "CArrowApplication.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CShader.h"
#include "CProgramLinker.h"

CArrowApplication::CArrowApplication(const char* title, int width, int height, GLuint program)
	: CGLApplication(title, width, height)
	, m_program(program)
{
}

CArrowApplication::~CArrowApplication()
{
	if (m_program)
	{
		glDeleteProgram(m_program);
	}

}

void CArrowApplication::InitShaders()
{
	// Проверяем поддержку геометрических шейдеров видеокартой
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error(
			"The OpenGL implementation does not support geometry shaders");
	}

	CShaderLoader loader;
	// Загружаем шейдеры
	m_vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	m_fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");
	m_geometryShader =
		loader.LoadShader(GL_GEOMETRY_SHADER, "shaders/geometry_shader.geom");

	// Создаем программный объект и присоединяем шейдеры к нему
	m_program.CreateProgram();
	m_program.AttachShader(m_vertexShader);
	m_program.AttachShader(m_fragmentShader);
	m_program.AttachShader(m_geometryShader);

	// Компилируем шейдеры
	CShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	compiler.CompileShader(m_geometryShader);
	compiler.CompileShader(m_fragmentShader);
	compiler.CheckStatus();

	// Компонуем программу и проверяем ее статус
	CProgramLinker linker;
	linker.LinkProgram(m_program);
	linker.CheckStatus();
}

void CArrowApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1);
	glColor3f(1, 1, 1);

	// Задаем параметры камеры
	glLoadIdentity();
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	InitShaders();
}

void CArrowApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
}

void CArrowApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Активируем шейдерную программу и задаем значения ее uniform-переменных
	glUseProgram(m_program);

	// Рисуем две точки в виде текстурированных прямоугольников
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0.0, -0.8, 0);
	glEnd();

	// Переключаемся на стандартный конвейер
	glUseProgram(0);
}