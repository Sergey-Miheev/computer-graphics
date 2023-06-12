#pragma once
#include "CProgram.h"
/*
����������� ���� ������������� ���������� ������������ �������
*/
template<bool t_managed>
class CProgramImpl : public CProgramBase
{
public:
	CProgramImpl(GLuint program = 0)
		:CProgramBase(program)
	{

	}

	// ������� ����������� ������ � ���������� ��� �������������
	GLuint CreateProgram()
	{
		if (t_managed && (Get() != 0))
		{
			DeleteProgram();
		}
		GLuint program = glCreateProgram();
		AttachProgram(program);
		return program;
	}

	// ��������� ������ �������� ������������ �������
	CProgramImpl& operator=(GLuint program)
	{
		// ������� ����� �������������� ���������
		if (t_managed && (Get() != 0) && (Get() != program))
		{
			DeleteProgram();
		}
		AttachProgram(program);
		return *this;
	}

	// ���������� ������������ �������
	~CProgramImpl()
	{
		// ������� ������ OpenGL (���� �� ����������� �������)
		if (t_managed && Get() != 0)
		{
			DeleteProgram();
		}
	}
};

// ��� "���������"
// (� �������������� ����������� ������ �����
// ������������ ������� OpenGL)
typedef CProgramImpl<true> CProgram;

// ��� "���������� ���������"
// (��� ��������������� ���������� �������� �����
// ������������ ������� OpenGL)
typedef CProgramImpl<false> CProgramHandle;
