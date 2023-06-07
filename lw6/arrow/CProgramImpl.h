#pragma once
//#include "CProgram.h"
///*
//����������� ���� ������������� ���������� ������������ �������
//*/
//template<bool t_managed>
//class CProgramImpl : public CProgramBase
//{
//public:
//	CProgramImpl(GLuint program = 0)
//		:CProgramBase(program)
//	{
//
//	}
//
//	// ������� ����������� ������ � ���������� ��� �������������
//	GLuint Create()
//	{
//		if (t_managed && (Get() != 0))
//		{
//			Delete();
//		}
//		GLuint program = glCreateProgram();
//		Attach(program);
//		return program;
//	}
//
//	// ��������� ������ �������� ������������ �������
//	CProgramImpl& operator=(GLuint program)
//	{
//		// ������� ����� �������������� ���������
//		if (t_managed && (Get() != 0) && (Get() != program))
//		{
//			Delete();
//		}
//		Attach(program);
//		return *this;
//	}
//
//	// ���������� ������������ �������
//	~CProgramImpl()
//	{
//		// ������� ������ OpenGL (���� �� ����������� �������)
//		if (t_managed && Get() != 0)
//		{
//			Delete();
//		}
//	}
//};
//
//// ��� "���������"
//// (� �������������� ����������� ������ �����
//// ������������ ������� OpenGL)
//typedef CProgramImpl<true> CProgram;
//
//// ��� "���������� ���������"
//// (��� ��������������� ���������� �������� �����
//// ������������ ������� OpenGL)
//typedef CProgramImpl<false> CProgramHandle;
