#define GLEW_STATIC
#include "glew.h"
#include "CArrowApplication.h"
#include "CShaderLoader.h"
#include "CShaderCompiler.h"
#include "CShader.cpp"
#include "CProgramLinker.h"

// ���� ������ �� ���������
const double CArrowApplication::FIELD_OF_VIEW = 80;

// ���������� �� ������� ��������� ���������� ������
const double CArrowApplication::ZNEAR = 1;

// ���������� �� ������� ��������� ���������� ������
const double CArrowApplication::ZFAR = 10;

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
	// ��������� ��������� �������������� �������� �����������
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error(
			"The OpenGL implementation does not support geometry shaders");
	}

	CShaderLoader loader;
	// ��������� �������
	m_vertexShader =
		loader.LoadShader(GL_VERTEX_SHADER, "shaders/vertex_shader.vert");
	m_fragmentShader =
		loader.LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment_shader.frag");
	m_geometryShader =
		loader.LoadShader(GL_GEOMETRY_SHADER, "shaders/geometry_shader.gsh");

	// ������� ����������� ������ � ������������ ������� � ����
	m_program.Create();
	m_program.AttachShader(m_vertexShader);
	m_program.AttachShader(m_fragmentShader);
	m_program.AttachShader(m_geometryShader);

	// ����������� �������
	CShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	compiler.CompileShader(m_geometryShader);
	compiler.CompileShader(m_fragmentShader);
	compiler.CheckStatus();

	// ������ ��������� ��������� ���������
	// ��� ������� ����������: �����
	m_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);
	// ���� �������� ����������: ����� �� ��������������
	m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);
	// ������������ ���������� ������, ����������� �������������� ��������
	// �� ���� �����. ��� ����� �� ���� ������������� ��� ����� 4
	m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 4);

	// ��������� ��������� � ��������� �� ������
	CProgramLinker linker;
	linker.LinkProgram(m_program);
	linker.CheckStatus();
}

void CArrowApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1);
	glColor3f(1, 1, 1);

	//glewInit();

	// ������ ��������� ������
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

	// ��������� ����������� ������ ���������� ������� ����
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, ZNEAR, ZFAR);

	glMatrixMode(GL_MODELVIEW);
}

void CArrowApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// ���������� ��������� ��������� � ������ �������� �� uniform-����������
	glUseProgram(m_program);

	// ������ ��� ����� � ���� ���������������� ���������������
	glBegin(GL_LINES);
		glVertex3f(-1.5, 0, 0);
		glVertex3f(1.5, 0.0, 0);
	glEnd();

	// ������������� �� ����������� ��������
	glUseProgram(0);
}