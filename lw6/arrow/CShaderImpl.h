#pragma once
#include "CShader.h"
/*
Шаблонная реализация класса "Шейдерный объект OpenGL"
Параметр t_managed определяет, будет ли время жизни
шейдерного объекта управляться классом CShaderImpl или нет
*/
template <bool t_managed>
class CShaderImpl : public CShaderBase
{
public:
	CShaderImpl(GLuint shader = 0)
		:CShaderBase(shader)
	{
	}

	// Оператор присваивания выполняет 
	CShaderImpl& operator=(GLuint shader)
	{
		// Удаляем текущий шейдерный объект только если:
		if (
			t_managed &&		// Класс управляет шейдерным объектом
			(Get() != 0) &&		// Задан текущий шейдерный объект
			(Get() != shader)	// И он не совпадает с переданным
			)
		{
			Delete();
		}
		Attach(shader);
		return *this;
	}

	// Создаем шейдер заданного типа
	GLuint CreateShader(GLenum type)
	{
		// Удаляем старый шейдерный объект в случае необходимости 
		// (если он задан и класс управляет шейдером)
		if ((Get() != 0) && t_managed)
		{
			Delete();
		}
		GLuint shader = glCreateShader(type);
		Attach(shader);
		return shader;
	}

	// Деструктор удалит текущий шейдерный объект (если класс управляет
	// шейдерным объектом)
	~CShaderImpl(void)
	{
		if (t_managed && (Get() != 0))
		{
			Delete();
		}
	}
};

// Тип "Шейдерный объект"
// (с автоматическим управлением времем жизни 
// шейдерного объекта OpenGL)
typedef CShaderImpl<true > CShader;
// Тип "Дескриптор шейдерного объекта" 
// (без автоматического управления временем
// жизни шейдерного объекта OpenGL)
typedef CShaderImpl<false> CShaderHandle;