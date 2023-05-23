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
	// ������� ��������� ��������
	CShaderLoader loader;
	// � ��������� � ��� ������� ��������� � ����������� �������
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "checker.vsh");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "checker.frag");

	// ������� ����������
	CShaderCompiler compiler;
	// � ��������� ���������� ��������
	compiler.CompileShader(vertexShader);
	compiler.CompileShader(fragmentShader);

	// ������� ��������� � ������������ � ��� �������
	m_program.Create();
	m_program.AttachShader(vertexShader);
	m_program.AttachShader(fragmentShader);

	// ��������� ��������� ������������������ ��������.
	// ���� ���� �� ���� �� �������� ��������������� � �������
	// ����� ��������� ����������
	compiler.CheckStatus();
	// ��� ���������, ������� ���������������� ��� �������

	// ������� �����������,
	CProgramLinker linker;
	// ��������� ��������� � ��� �������
	linker.LinkProgram(m_program);

	// ��������� ��������� ���������������� ��������
	// ���� ��� ���������� �������� ������, ��
	// ����� ��������� ����������
	linker.CheckStatus();
	// ��� ���������

}

void CFlagApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1);
	glColor3f(1, 1, 1);

	glewInit();

	// ������ ��������� ������
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

	// ��������� ����������� ������ ���������� ������� ����
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

	// ������ �������
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