#pragma once
#include "CShader.h"
/*
��������� ���������� ������ "��������� ������ OpenGL"
�������� t_managed ����������, ����� �� ����� �����
���������� ������� ����������� ������� CShaderImpl ��� ���
*/
template <bool t_managed>
class CShaderImpl : public CShaderBase
{
public:
	CShaderImpl(GLuint shader = 0)
		:CShaderBase(shader)
	{
	}

	// �������� ������������ ��������� 
	CShaderImpl& operator=(GLuint shader)
	{
		// ������� ������� ��������� ������ ������ ����:
		if (
			t_managed &&		// ����� ��������� ��������� ��������
			(Get() != 0) &&		// ����� ������� ��������� ������
			(Get() != shader)	// � �� �� ��������� � ����������
			)
		{
			Delete();
		}
		Attach(shader);
		return *this;
	}

	// ������� ������ ��������� ����
	GLuint CreateShader(GLenum type)
	{
		// ������� ������ ��������� ������ � ������ ������������� 
		// (���� �� ����� � ����� ��������� ��������)
		if ((Get() != 0) && t_managed)
		{
			Delete();
		}
		GLuint shader = glCreateShader(type);
		Attach(shader);
		return shader;
	}

	// ���������� ������ ������� ��������� ������ (���� ����� ���������
	// ��������� ��������)
	~CShaderImpl(void)
	{
		if (t_managed && (Get() != 0))
		{
			Delete();
		}
	}
};

// ��� "��������� ������"
// (� �������������� ����������� ������ ����� 
// ���������� ������� OpenGL)
typedef CShaderImpl<true > CShader;
// ��� "���������� ���������� �������" 
// (��� ��������������� ���������� ��������
// ����� ���������� ������� OpenGL)
typedef CShaderImpl<false> CShaderHandle;