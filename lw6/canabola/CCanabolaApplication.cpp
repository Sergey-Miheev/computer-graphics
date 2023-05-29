#define GLEW_STATIC
#include "glew.h"
#include "CCanabolaApplication.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CShader.cpp"
#include "CProgramLinker.h"

// Угол обзора по вертикали
const double CCanabolaApplication::FIELD_OF_VIEW = 80;

// Расстояине до ближней плоскости отсчечения камеры
const double CCanabolaApplication::ZNEAR = 1;

// Расстояине до дальней плоскости отсчечения камеры
const double CCanabolaApplication::ZFAR = 10;

CCanabolaApplication::CCanabolaApplication(const char* title, int width, int height, GLuint program)
	: CGLApplication(title, width, height)
	, m_program(program)
{
}

CCanabolaApplication::~CCanabolaApplication()
{
	if (m_program)
	{
		glDeleteProgram(m_program);
	}

}

void CCanabolaApplication::InitShaders()
{
	// Создаем загрузчик шейдеров
	CShaderLoader loader;
	// И загружаем с его помощью вершинный и фрагментный шейдеры
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");

	// Создаем компилятор
	CShaderCompiler compiler;
	// и запускаем компиляцию шейдеров
	compiler.CompileShader(vertexShader);
	compiler.CompileShader(fragmentShader);

	// Создаем программу и присоединяем к ней шейдеры
	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	// Проверяем состояние скомпилированности шейдеров.
	// Если хотя бы один из шейдеров скомпилировался с ошибкой
	// будет выброшено исключение
	compiler.CheckStatus();
	// Все нормально, шейдеры скомпилировались без проблем

	// Создаем компоновщик,
	CProgramLinker linker;
	// компонуем программу с его помощью
	linker.LinkProgram(m_program);

	// Проверяем состояние скомпонованности программ
	// Если при компоновке возникла ошибка, то
	// будет выброшено исключение
	linker.CheckStatus();
	// Все нормально
}

void CCanabolaApplication::OnInit()
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

void CCanabolaApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, ZNEAR, ZFAR);

	glMatrixMode(GL_MODELVIEW);
}

void CCanabolaApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	#define M_PI 3.1415926535897932384626433832795

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	{
		for (double x = 0; x <= 2 * M_PI; x += M_PI / 1000)
		{
			glVertex2d(x, 0);
		}
	}
	glEnd();

	glUseProgram(0);
}