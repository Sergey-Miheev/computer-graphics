#define GLEW_STATIC
#include "glew.h"
#include "CCanabolaApplication.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CShader.cpp"
#include "CProgramLinker.h"

// ���� ������ �� ���������
const double CCanabolaApplication::FIELD_OF_VIEW = 80;

// ���������� �� ������� ��������� ���������� ������
const double CCanabolaApplication::ZNEAR = 1;

// ���������� �� ������� ��������� ���������� ������
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
	// ������� ��������� ��������
	CShaderLoader loader;
	// � ��������� � ��� ������� ��������� � ����������� �������
	CShader vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	CShader fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");

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

void CCanabolaApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1);
	glColor3f(1, 1, 1);

	// ������ ��������� ������
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

	// ��������� ����������� ������ ���������� ������� ����
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