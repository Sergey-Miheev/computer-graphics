#include <iostream>
#include <vector>
#include <assert.h>
#define GLEW_STATIC
#include "glew.h"
#include "GL/glut.h"

//����� "������� ����������� ������ OpenGL"
class CProgramBase
{
protected:
	CProgramBase(GLuint program = 0)
		:m_program(program)
	{
	}

	// ��������� ���������� ����������, ����� ������ ���� �������
	// ��������� ������ ����� CPrograBase
	~CProgramBase()
	{
	}
public:
	// �������� ������������� ������������� ������������ �������
	operator GLuint()const
	{
		return m_program;
	}

	// ������� ������������� ������������� ������������ �������
	GLuint Get()const
	{
		return m_program;
	}

	// ������ �������� ������������ �������
	void SetParameter(GLenum pname, GLint value)
	{
		assert(m_program);
		glProgramParameteri(m_program, pname, value);
	}

	// ������� ����������� ������
	void Delete()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	// ����������� � ������� ������ ���������� ������������ �������,
	// ��������� ����� ������������
	GLuint Attach(GLuint program)
	{
		GLuint tmp = m_program;
		m_program = program;
		return tmp;
	}

	/*
	������������ � ��������� ������ � ��������� ���������������
	*/
	void AttachShader(GLuint shader)
	{
		assert(m_program != 0);
		glAttachShader(m_program, shader);
	}

	// ����������� ������ � ��������� ���������������
	void DetachShader(GLuint shader)
	{
		assert(m_program != 0);
		glDetachShader(m_program, shader);
	}

	// ��������� ���������� ���������
	void Link()const
	{
		assert(m_program);
		glLinkProgram(m_program);
	}

	// ���������, �������� �� ���������� ������ ��������� ���������
	// � ������� ���������� OpenGL
	void Validate()const
	{
		assert(m_program);
		glValidateProgram(m_program);
	}

	// �������� ���������� � ��������� � ��������� ����
	void GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
	{
		assert(m_program != 0);
		glGetProgramInfoLog(m_program, bufSize, length, infoLog);
	}

	// �������� ���������� � ��������� � ��������� ����
	// (���������� �������)
	std::string GetInfoLog()const;

	// ������ �������� ������������ �������
	void GetParameter(GLenum pname, GLint* param)const
	{
		assert(m_program != 0);
		glGetProgramiv(m_program, pname, param);
	}

	// �������� ������������ uniform-���������� � 
	// ��������� ������
	GLint GetUniformLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetUniformLocation(m_program, name);
	}

	// �������� ������������ ������������ ���������� 
	// � �������� ������.
	GLint GetAttribLocation(const GLchar* name)const
	{
		assert(m_program);
		return glGetAttribLocation(m_program, name);
	}

	// ���������� ���������� �������� uniform-����������
	GLuint GetActiveUniforms()const
	{
		return GetParameter(GL_ACTIVE_UNIFORMS);
	}

	// ���������� ���������� �������� attribute-����������
	GLuint GetActiveAttributes()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTES);
	}

	// ���������� ������������ ����� ��� �������� ����� 
	// uniform-���������� ���������
	GLuint GetActiveUniformMaxLength()const
	{
		return GetParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH);
	}

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	void GetActiveUniform(
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
	std::string GetActiveUniform(GLuint index, GLint* size, GLenum* type)const
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
	GLuint GetActiveAttributeMaxLength()const
	{
		return GetParameter(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	// �������� ���������� �� �����, ����, ����� � ������� ��������
	// attribute-����������
	void GetActiveAttrib(
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
	std::string GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const
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
	GLint GetParameter(GLenum pname)const
	{
		GLint value = 0;
		GetParameter(pname, &value);
		return value;
	}
private:
	CProgramBase(CProgramBase const&);
	CProgramBase& operator=(CProgramBase const&);
	GLuint m_program;
};