#include "CShader.h"
#include <assert.h>

// ������ �������� ��� �������
void CShaderBase::SetSource(GLsizei count, const GLchar** strings, const GLint* lengths)
{
	assert(m_shader != 0);

	glShaderSource(m_shader, count, strings, lengths);
}

// ������ �������� ��� ������� (� ����� ������)
void CShaderBase::SetSource(const GLchar* source, GLint length)
{
	const GLchar** ppSource = &source;
	SetSource(1, ppSource, &length);
}

// ������ �������� ��� ������� (���� ASCIIZ-������)
void CShaderBase::SetSource(const GLchar* source)
{
	const GLchar** ppSource = &source;
	SetSource(1, ppSource, NULL);
}

// �������� �������� ���������� ��������� �������
void CShaderBase::GetParameter(GLenum pname, GLint* param)const
{
	assert(m_shader != 0);
	glGetShaderiv(m_shader, pname, param);
}

// ���������� ������� ����������� ������
GLint CShaderBase::GetParameter(GLenum pname)const
{
	GLint value;
	GetParameter(pname, &value);
	return value;
}

// �������� �������������� ��� �� �������
void CShaderBase::GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
{
	assert(m_shader != 0);
	glGetShaderInfoLog(m_shader, bufSize, length, infoLog);
}

// �������� �������������� ��� �� �������
	// (���������� �������)
std::string CShaderBase::GetInfoLog()const
{
	GLint length = GetParameter(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		GetInfoLog(length, &length, &buffer[0]);
		std::string log(&buffer[0]);
		return log;
	}
	else
	{
		return std::string();
	}
}

// �������� ������������� ���������� �������
CShaderBase::operator GLuint()const
{
	return m_shader;
}

// �������� ������������� ���������� ������� (�������������� �������)
GLuint CShaderBase::Get()const
{
	return m_shader;
}

// ����������� ������
void CShaderBase::Compile()
{
	assert(m_shader != 0);
	glCompileShader(m_shader);
}

// ������������ ��������� ������ � ������ � ����������
	// ���������� ����� ���������������
GLuint CShaderBase::Attach(GLuint shader)
{
	GLuint tmp = m_shader;
	m_shader = shader;
	return tmp;
}

// ����������� ��������� ������
GLuint CShaderBase::Detach()
{
	return Attach(0);
}

// ������� ��������� ������
void CShaderBase::Delete()
{
	assert(m_shader != 0);
	if (m_shader != 0)
	{
		glDeleteShader(Detach());
		m_shader = 0;
	}
}

