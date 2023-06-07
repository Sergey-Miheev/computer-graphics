#pragma once
//#include "CProgram.h"
///*
//Управляемая либо неуправляемая реализация программного объекта
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
//	// Создаем программный объект и возвращаем его идентификатор
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
//	// Выполняем замену текущего программного объекта
//	CProgramImpl& operator=(GLuint program)
//	{
//		// Удаляем ранее присоединенную программу
//		if (t_managed && (Get() != 0) && (Get() != program))
//		{
//			Delete();
//		}
//		Attach(program);
//		return *this;
//	}
//
//	// Деструктор программного объекта
//	~CProgramImpl()
//	{
//		// удаляем объект OpenGL (если он управляется классом)
//		if (t_managed && Get() != 0)
//		{
//			Delete();
//		}
//	}
//};
//
//// Тип "Программа"
//// (с автоматическим управлением времем жизни
//// программного объекта OpenGL)
//typedef CProgramImpl<true> CProgram;
//
//// Тип "Дескриптор программы"
//// (без автоматического управления временем жизни
//// программного объекта OpenGL)
//typedef CProgramImpl<false> CProgramHandle;
