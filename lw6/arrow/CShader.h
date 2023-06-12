#pragma once
#include <iostream>
#include <vector>
#define GLEW_STATIC
#include "glew.h"
#include "GL/glut.h"
#include <assert.h>

/*
Базовый класс для работы с шейдерный объектом OpenGL
*/
class CShaderBase
{
	// Защищенные конструктор и деструктор сделают 
	// возможным использование данного класса только 
	// для его потомков
protected:
	CShaderBase(GLuint shader = 0)
		:m_shader(shader)
	{
	}

	// Объявляем деструктор защищенным, т.к. в противном
	// случае компилятор сделал бы его публичным
	// Объявлять деструктор виртуальным нет необходимости
	// т.к. деструктор защищен от вызова извне, а значит
	// удалить CShaderBase напрямую не получится (только удалив
	// его наследника)
	~CShaderBase()
	{
		// Данный деструктор не делает ничего
		// Освобождением ресурсов будет заниматься 
		// класс-потомок
	}
public:
	// Задаем исходный код шейдера
	void SetSource(GLsizei count, const GLchar** strings, const GLint* lengths);

	// Задаем исходный код шейдера (в одной строке)
	void SetSource(const GLchar* source, GLint length);

	// Задаем исходный код шейдера (одна ASCIIZ-строка)
	void SetSource(const GLchar* source);

	// Получаем значение некоторого параметра шейдера
	void GetParameter(GLenum pname, GLint* param)const;

	// Упрощенный вариант предыдущего метода
	GLint GetParameter(GLenum pname)const;

	// Получаем информационный лог от шейдера
	void GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// Получаем информационный лог от шейдера
	// (упрощенный вариант)
	std::string GetInfoLog()const;

	// Получаем идентификатор шейдерного объекта
	operator GLuint()const;

	// Получаем идентификатор шейдерного объекта (альтернативный вариант)
	GLuint Get()const;

	// Компилируем ешйдер
	void Compile();

	// Присоединяем шейдерный объект к классу и возвращаем
	// дескриптор ранее присоединенного
	GLuint Attach(GLuint shader);

	// Отсоединяем шейдерный объект
	GLuint Detach();

	// Удаляем шейдерный объект
	void Delete();

private:
	// Делаем недоступными конструктор копирования
	// и оператор присваивания
	CShaderBase(CShaderBase const&);
	CShaderBase& operator=(CShaderBase const&);

	GLuint m_shader;
};

///*
//Шаблонная реализация класса "Шейдерный объект OpenGL"
//Параметр t_managed определяет, будет ли время жизни
//шейдерного объекта управляться классом CShaderImpl или нет
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
//	// Оператор присваивания выполняет 
//	CShaderImpl& operator=(GLuint shader)
//	{
//		// Удаляем текущий шейдерный объект только если:
//		if (
//			t_managed &&		// Класс управляет шейдерным объектом
//			(Get() != 0) &&		// Задан текущий шейдерный объект
//			(Get() != shader)	// И он не совпадает с переданным
//			)
//		{
//			Delete();
//		}
//		Attach(shader);
//		return *this;
//	}
//
//	// Создаем шейдер заданного типа
//	GLuint CreateShader(GLenum type)
//	{
//		// Удаляем старый шейдерный объект в случае необходимости 
//		// (если он задан и класс управляет шейдером)
//		if ((Get() != 0) && t_managed)
//		{
//			Delete();
//		}
//		GLuint shader = glCreateShader(type);
//		Attach(shader);
//		return shader;
//	}
//
//	// Деструктор удалит текущий шейдерный объект (если класс управляет
//	// шейдерным объектом)
//	~CShaderImpl(void)
//	{
//		if (t_managed && (Get() != 0))
//		{
//			Delete();
//		}
//	}
//};
//
//// Тип "Шейдерный объект"
//// (с автоматическим управлением времем жизни 
//// шейдерного объекта OpenGL)
//typedef CShaderImpl<true > CShader;
//// Тип "Дескриптор шейдерного объекта" 
//// (без автоматического управления временем
//// жизни шейдерного объекта OpenGL)
//typedef CShaderImpl<false> CShaderHandle;