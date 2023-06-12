#include "CProgram.h"

// ������� ������������� ������������� ������������ �������
GLuint CProgramBase::Get()const
{
	return m_program;
}

// ������ �������� ������������ �������
void CProgramBase::SetParameter(GLenum pname, GLint value)
{
	assert(m_program);
	glProgramParameteri(m_program, pname, value);
}

// ������� ����������� ������
void CProgramBase::DeleteProgram()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

// ����������� � ������� ������ ���������� ������������ �������,
// ��������� ����� ������������
GLuint CProgramBase::AttachProgram(GLuint program)
{
	GLuint tmp = m_program;
	m_program = program;
	return tmp;
}

//������������ � ��������� ������ � ��������� ���������������
void CProgramBase::AttachShader(GLuint shader)
{
	assert(m_program != 0);
	glAttachShader(m_program, shader);
}

// ����������� ������ � ��������� ���������������
void CProgramBase::DetachShader(GLuint shader)
{
	assert(m_program != 0);
	glDetachShader(m_program, shader);
}

// ��������� ���������� ���������
void CProgramBase::LinkProgram()const
{
	assert(m_program);
	glLinkProgram(m_program);
}

// ���������, �������� �� ���������� ������ ��������� ���������
	// � ������� ���������� OpenGL
void CProgramBase::Validate()const
{
	assert(m_program);
	glValidateProgram(m_program);
}

// �������� ���������� � ��������� � ��������� ����
void CProgramBase::GetInfoLogProgram(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
{
	assert(m_program != 0);
	glGetProgramInfoLog(m_program, bufSize, length, infoLog);
}

// �������� ���������� � ��������� � ��������� ����
	// (���������� �������)
std::string CProgramBase::GetInfoLogProgram()const
{
	GLint length = GetParameterOfProgram(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		GetInfoLogProgram(length, &length, &buffer[0]);
		std::string log(&buffer[0], length - 1);
		return log;
	}
	else
	{
		return std::string();
	}
}

// ������ �������� ������������ �������
void CProgramBase::GetParameterOfProgram(GLenum pname, GLint* param)const
{
	assert(m_program != 0);
	glGetProgramiv(m_program, pname, param);
}

// �������� ������������ uniform-���������� � 
	// ��������� ������
GLint CProgramBase::GetUniformLocation(const GLchar* name)const
{
	assert(m_program);
	return glGetUniformLocation(m_program, name);
}

// �������� ������������ ������������ ���������� 
	// � �������� ������.
GLint CProgramBase::GetAttribLocation(const GLchar* name)const
{
	assert(m_program);
	return glGetAttribLocation(m_program, name);
}

// ���������� ���������� �������� uniform-����������
GLuint CProgramBase::GetActiveUniforms()const
{
	return GetParameterOfProgram(GL_ACTIVE_UNIFORMS);
}

// ���������� ���������� �������� attribute-����������
GLuint CProgramBase::GetActiveAttributes()const
{
	return GetParameterOfProgram(GL_ACTIVE_ATTRIBUTES);
}

// ���������� ������������ ����� ��� �������� ����� 
// uniform-���������� ���������
GLuint CProgramBase::GetActiveUniformMaxLength()const
{
	return GetParameterOfProgram(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

// �������� ���������� �� �����, ���� � ������� uniform-����������
void CProgramBase::GetActiveUniform(
	GLuint index, GLsizei maxLength,
	GLsizei* length, GLint* size,
	GLenum* type, GLchar* name)const
{
	assert(m_program);
	assert(index < GetActiveUniforms());
	glGetActiveUniform(
		m_program, index, maxLength, length, size, type, name);
}

// �������� ���������� �� �����, ���� � ������� uniform-����������
	// ����� ������� ��������
std::string CProgramBase::GetActiveUniform(GLuint index, GLint* size, GLenum* type)const
{
	// ������ ������ ������ ��� �������� �����
	GLuint bufferLength = GetActiveUniformMaxLength();
	if (!bufferLength)
	{
		// ��� �������� uniform ����������
		return std::string();
	}
	std::vector<char> buffer(bufferLength);
	GLsizei nameLength = 0;

	// �������� ���, ��� � ������ ����������
	GetActiveUniform(
		index, bufferLength, &nameLength, size, type, &buffer[0]);

	// ��������� �� � ��������� �������������
	return std::string(&buffer[0], &buffer[nameLength]);
}

// ���������� ������������ ����� ��� �������� ����� 
	// attribute-���������� ���������
GLuint CProgramBase::GetActiveAttributeMaxLength()const
{
	return GetParameterOfProgram(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

// �������� ���������� �� �����, ����, ����� � ������� ��������
	// attribute-����������
void CProgramBase::GetActiveAttrib(
	GLuint index, GLsizei maxLength,
	GLsizei* length, GLint* size,
	GLenum* type, GLchar* name)const
{
	assert(m_program);
	assert(index < GetActiveAttributes());
	glGetActiveAttrib(m_program, index, maxLength, length, size, type, name);
}

// �������� ���������� �� �����, ������� � ���� ��������
	// attribute-���������� ����� ������� ��������
std::string CProgramBase::GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const
{
	GLuint bufferLength = GetActiveAttributeMaxLength();
	if (!bufferLength)
	{
		// ��� �������� attribute-����������
		return std::string();
	}
	std::vector<char> buffer(bufferLength);
	GLsizei nameLength = 0;

	// �������� ���, ��� � ������ ����������
	GetActiveAttrib(
		index, bufferLength,
		&nameLength, size,
		type, &buffer[0]);

	// ��������� �� � ��������� �������������
	return std::string(&buffer[0], &buffer[nameLength]);
}

// �������� �������� ������������ �������
GLint CProgramBase::GetParameterOfProgram(GLenum pname)const
{
	GLint value = 0;
	GetParameterOfProgram(pname, &value);
	return value;
}

