#include <iostream>
#include <vector>
#include <assert.h>
#define GLEW_STATIC
#include "glew.h"
#include "GL/glut.h"
// не забыть удалить программу через delete
//Класс "Базовый программный объект OpenGL"
class CProgramBase
{
protected:
	CProgramBase(GLuint program = 0)
		:m_program(program)
	{
	}

	// Объявляем деструктор защищенным, чтобы нельзя было удалить
	// экземпляр класса через CPrograBase
	~CProgramBase()
	{
	}
public:
	// Получаем целочисленный идентификатор программного объекта
	operator GLuint()const
	{
		return m_program;
	}

	// Получае целочисленный идентификатор программного объекта
	GLuint Get()const;

	// Задаем параметр программного объекта
	void SetParameter(GLenum pname, GLint value);

	// Удаляем программный объект
	void DeleteProgram();

	// Присоединям к объекту класса дескриптор программного объекта,
	// возвращая ранее существующий
	GLuint AttachProgram(GLuint program);
	
	//Присоединяем к программе шейдер с указанным идентификатором
	void AttachShader(GLuint shader);

	// Отсоединяем шейдер с указанным идентификатором
	void DetachShader(GLuint shader);

	// Выполняем компоновку программы
	void LinkProgram()const;

	// Проверяем, возможна ли корректная работа шейдерной программы
	// с текущим состоянием OpenGL
	void Validate()const;

	// Получаем информацию о программе в текстовом виде
	void GetInfoLogProgram(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const;

	// Получаем информацию о программе в текстовом виде
	// (упрощенный вариант)
	std::string GetInfoLogProgram()const;

	// Задаем параметр программного объекта
	void GetParameterOfProgram(GLenum pname, GLint* param)const;

	// Получаем расположение uniform-переменной с 
	// указанным именем
	GLint GetUniformLocation(const GLchar* name)const;

	// Получаем расположение атрибутивной переменной 
	// с заданным именем.
	GLint GetAttribLocation(const GLchar* name)const;

	// Возвращаем количество активных uniform-переменных
	GLuint GetActiveUniforms()const;

	// Возвращаем количество активных attribute-переменных
	GLuint GetActiveAttributes()const;

	// Возвращаем максимальную длину для хранения имени 
	// uniform-переменной программы
	GLuint GetActiveUniformMaxLength()const;

	// Получаем информацию об имени, типе и размере uniform-переменной
	void GetActiveUniform(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// Получаем информацию об имени, типе и размере uniform-переменной
	// более простым способом
	std::string GetActiveUniform(GLuint index, GLint* size, GLenum* type)const;

	// Возвращаем максимальную длину для хранения имени 
	// attribute-переменной программы
	GLuint GetActiveAttributeMaxLength()const;

	// Получаем информацию об имени, типе, длине и размере активной
	// attribute-переменной
	void GetActiveAttrib(
		GLuint index, GLsizei maxLength,
		GLsizei* length, GLint* size,
		GLenum* type, GLchar* name)const;

	// Получаем информацию об имени, размере и типе активной
	// attribute-переменной более простым способом
	std::string GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const;

	// Получаем параметр программного объекта
	GLint GetParameterOfProgram(GLenum pname)const;
private:
	CProgramBase(CProgramBase const&);
	CProgramBase& operator=(CProgramBase const&);
	GLuint m_program;
};