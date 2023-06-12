#pragma once
#include <iostream>
#include <vector>
#define GLEW_STATIC
#include "glew.h"
#include "GL/glut.h"
#include <assert.h>

/*
������� ����� ��� ������ � ��������� �������� OpenGL
*/
class CShaderBase
{
	// ���������� ����������� � ���������� ������� 
	// ��������� ������������� ������� ������ ������ 
	// ��� ��� ��������
protected:
	CShaderBase(GLuint shader = 0)
		:m_shader(shader)
	{
	}

	// ��������� ���������� ����������, �.�. � ���������
	// ������ ���������� ������ �� ��� ���������
	// ��������� ���������� ����������� ��� �������������
	// �.�. ���������� ������� �� ������ �����, � ������
	// ������� CShaderBase �������� �� ��������� (������ ������
	// ��� ����������)
	~CShaderBase()
	{
		// ������ ���������� �� ������ ������
		// ������������� �������� ����� ���������� 
		// �����-�������
	}
public:
	// ������ �������� ��� �������
	void SetSource(GLsizei count, const GLchar** strings, const GLint* lengths);

	// ������ �������� ��� ������� (� ����� ������)
	void SetSource(const GLchar* source, GLint length);

	// ������ �������� ��� ������� (���� ASCIIZ-������)
	void SetSource(const GLchar* source);

	// �������� �������� ���������� ��������� �������
	void GetParameter(GLenum pname, GLint* param)const;

	// ���������� ������� ����������� ������
	GLint GetParameter(GLenum pname)const;

	// �������� �������������� ��� �� �������
	void GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// �������� �������������� ��� �� �������
	// (���������� �������)
	std::string GetInfoLog()const;

	// �������� ������������� ���������� �������
	operator GLuint()const;

	// �������� ������������� ���������� ������� (�������������� �������)
	GLuint Get()const;

	// ����������� ������
	void Compile();

	// ������������ ��������� ������ � ������ � ����������
	// ���������� ����� ���������������
	GLuint Attach(GLuint shader);

	// ����������� ��������� ������
	GLuint Detach();

	// ������� ��������� ������
	void Delete();

private:
	// ������ ������������ ����������� �����������
	// � �������� ������������
	CShaderBase(CShaderBase const&);
	CShaderBase& operator=(CShaderBase const&);

	GLuint m_shader;
};

///*
//��������� ���������� ������ "��������� ������ OpenGL"
//�������� t_managed ����������, ����� �� ����� �����
//���������� ������� ����������� ������� CShaderImpl ��� ���
//*/
//template <bool t_managed>
//class CShaderImpl : public CShaderBase
//{
//public:
//	CShaderImpl(GLuint shader = 0)
//		:CShaderBase(shader)
//	{
//	}
//
//	// �������� ������������ ��������� 
//	CShaderImpl& operator=(GLuint shader)
//	{
//		// ������� ������� ��������� ������ ������ ����:
//		if (
//			t_managed &&		// ����� ��������� ��������� ��������
//			(Get() != 0) &&		// ����� ������� ��������� ������
//			(Get() != shader)	// � �� �� ��������� � ����������
//			)
//		{
//			Delete();
//		}
//		Attach(shader);
//		return *this;
//	}
//
//	// ������� ������ ��������� ����
//	GLuint CreateShader(GLenum type)
//	{
//		// ������� ������ ��������� ������ � ������ ������������� 
//		// (���� �� ����� � ����� ��������� ��������)
//		if ((Get() != 0) && t_managed)
//		{
//			Delete();
//		}
//		GLuint shader = glCreateShader(type);
//		Attach(shader);
//		return shader;
//	}
//
//	// ���������� ������ ������� ��������� ������ (���� ����� ���������
//	// ��������� ��������)
//	~CShaderImpl(void)
//	{
//		if (t_managed && (Get() != 0))
//		{
//			Delete();
//		}
//	}
//};
//
//// ��� "��������� ������"
//// (� �������������� ����������� ������ ����� 
//// ���������� ������� OpenGL)
//typedef CShaderImpl<true > CShader;
//// ��� "���������� ���������� �������" 
//// (��� ��������������� ���������� ��������
//// ����� ���������� ������� OpenGL)
//typedef CShaderImpl<false> CShaderHandle;