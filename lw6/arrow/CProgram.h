#include <iostream>
#include <vector>
#include <assert.h>
#define GLEW_STATIC
#include "glew.h"
#include "GL/glut.h"
// �� ������ ������� ��������� ����� delete
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
	GLuint Get()const;

	// ������ �������� ������������ �������
	void SetParameter(GLenum pname, GLint value);

	// ������� ����������� ������
	void DeleteProgram();

	// ����������� � ������� ������ ���������� ������������ �������,
	// ��������� ����� ������������
	GLuint AttachProgram(GLuint program);
	
	//������������ � ��������� ������ � ��������� ���������������
	void AttachShader(GLuint shader);

	// ����������� ������ � ��������� ���������������
	void DetachShader(GLuint shader);

	// ��������� ���������� ���������
	void LinkProgram()const;

	// ���������, �������� �� ���������� ������ ��������� ���������
	// � ������� ���������� OpenGL
	void Validate()const;

	// �������� ���������� � ��������� � ��������� ����
	void GetInfoLogProgram(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// �������� ���������� � ��������� � ��������� ����
	// (���������� �������)
	std::string GetInfoLogProgram()const;

	// ������ �������� ������������ �������
	void GetParameterOfProgram(GLenum pname, GLint* param)const;

	// �������� ������������ uniform-���������� � 
	// ��������� ������
	GLint GetUniformLocation(const GLchar* name)const;

	// �������� ������������ ������������ ���������� 
	// � �������� ������.
	GLint GetAttribLocation(const GLchar* name)const;

	// ���������� ���������� �������� uniform-����������
	GLuint GetActiveUniforms()const;

	// ���������� ���������� �������� attribute-����������
	GLuint GetActiveAttributes()const;

	// ���������� ������������ ����� ��� �������� ����� 
	// uniform-���������� ���������
	GLuint GetActiveUniformMaxLength()const;

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	void GetActiveUniform(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// �������� ���������� �� �����, ���� � ������� uniform-����������
	// ����� ������� ��������
	std::string GetActiveUniform(GLuint index, GLint* size, GLenum* type)const;

	// ���������� ������������ ����� ��� �������� ����� 
	// attribute-���������� ���������
	GLuint GetActiveAttributeMaxLength()const;

	// �������� ���������� �� �����, ����, ����� � ������� ��������
	// attribute-����������
	void GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// �������� ���������� �� �����, ������� � ���� ��������
	// attribute-���������� ����� ������� ��������
	std::string GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const;

	// �������� �������� ������������ �������
	GLint GetParameterOfProgram(GLenum pname)const;
private:
	CProgramBase(CProgramBase const&);
	CProgramBase& operator=(CProgramBase const&);
	GLuint m_program;
};