#define GLEW_STATIC
#include "glew.h"
#include "CFlagApplication.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CShader.cpp"
#include "CProgramLinker.h"

CFlagApplication::CFlagApplication(const char* title, int width, int height, GLuint program)
	: CGLApplication(title, width, height)
	, m_program(program)
{
}

CFlagApplication::~CFlagApplication()
{
	if (m_program)
	{
		glDeleteProgram(m_program);
	}

}

void CFlagApplication::InitShaders()
{
	// Создаем загрузчик шейдеров
	CShaderLoader loader;
	// И загружаем с его помощью вершинный и фрагментный шейдеры
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "checker.vsh");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "checker.frag");

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

void CFlagApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(1, 1, 1);

	glewInit();

	// Задаем параметры камеры
	glLoadIdentity();
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	InitShaders();
}

void CFlagApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect, +aspect, -1, 1, 0, 10);
	glMatrixMode(GL_MODELVIEW);

}

void CFlagApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_program);

	// Рисуем квадрат
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-0.8, -0.8);

		glTexCoord2f(4, 0);
		glVertex2f(0.8, -0.8);

		glTexCoord2f(4, 4);
		glVertex2f(0.8, 0.8);

		glTexCoord2f(0, 4);
		glVertex2f(-0.8, 0.8);
	}
	glEnd();

	glUseProgram(0);
}