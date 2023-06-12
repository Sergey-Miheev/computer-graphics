#include "CProgram.h"

// Получае целочисленный идентификатор программного объекта
GLuint CProgramBase::Get()const
{
	return m_program;
}

// Задаем параметр программного объекта
void CProgramBase::SetParameter(GLenum pname, GLint value)
{
	assert(m_program);
	glProgramParameteri(m_program, pname, value);
}

// Удаляем программный объект
void CProgramBase::DeleteProgram()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

// Присоединям к объекту класса дескриптор программного объекта,
// возвращая ранее существующий
GLuint CProgramBase::AttachProgram(GLuint program)
{
	GLuint tmp = m_program;
	m_program = program;
	return tmp;
}

//Присоединяем к программе шейдер с указанным идентификатором
void CProgramBase::AttachShader(GLuint shader)
{
	assert(m_program != 0);
	glAttachShader(m_program, shader);
}

// Отсоединяем шейдер с указанным идентификатором
void CProgramBase::DetachShader(GLuint shader)
{
	assert(m_program != 0);
	glDetachShader(m_program, shader);
}

// Выполняем компоновку программы
void CProgramBase::LinkProgram()const
{
	assert(m_program);
	glLinkProgram(m_program);
}

// Проверяем, возможна ли корректная работа шейдерной программы
	// с текущим состоянием OpenGL
void CProgramBase::Validate()const
{
	assert(m_program);
	glValidateProgram(m_program);
}

// Получаем информацию о программе в текстовом виде
void CProgramBase::GetInfoLogProgram(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
{
	assert(m_program != 0);
	glGetProgramInfoLog(m_program, bufSize, length, infoLog);
}

// Получаем информацию о программе в текстовом виде
	// (упрощенный вариант)
std::string CProgramBase::GetInfoLogProgram()const
{
	GLint length = GetParameterOfProgram(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		GetInfoLogProgram(length, &length, &buffer[0]);
		std::string log(&buffer[0], length - 1);
		return log;
	}
	else
	{
		return std::string();
	}
}

// Задаем параметр программного объекта
void CProgramBase::GetParameterOfProgram(GLenum pname, GLint* param)const
{
	assert(m_program != 0);
	glGetProgramiv(m_program, pname, param);
}

// Получаем расположение uniform-переменной с 
	// указанным именем
GLint CProgramBase::GetUniformLocation(const GLchar* name)const
{
	assert(m_program);
	return glGetUniformLocation(m_program, name);
}

// Получаем расположение атрибутивной переменной 
	// с заданным именем.
GLint CProgramBase::GetAttribLocation(const GLchar* name)const
{
	assert(m_program);
	return glGetAttribLocation(m_program, name);
}

// Возвращаем количество активных uniform-переменных
GLuint CProgramBase::GetActiveUniforms()const
{
	return GetParameterOfProgram(GL_ACTIVE_UNIFORMS);
}

// Возвращаем количество активных attribute-переменных
GLuint CProgramBase::GetActiveAttributes()const
{
	return GetParameterOfProgram(GL_ACTIVE_ATTRIBUTES);
}

// Возвращаем максимальную длину для хранения имени 
// uniform-переменной программы
GLuint CProgramBase::GetActiveUniformMaxLength()const
{
	return GetParameterOfProgram(GL_ACTIVE_UNIFORM_MAX_LENGTH);
}

// Получаем информацию об имени, типе и размере uniform-переменной
void CProgramBase::GetActiveUniform(
	GLuint index, GLsizei maxLength,
	GLsizei* length, GLint* size,
	GLenum* type, GLchar* name)const
{
	assert(m_program);
	assert(index < GetActiveUniforms());
	glGetActiveUniform(
		m_program, index, maxLength, length, size, type, name);
}

// Получаем информацию об имени, типе и размере uniform-переменной
	// более простым способом
std::string CProgramBase::GetActiveUniform(GLuint index, GLint* size, GLenum* type)const
{
	// Узнаем размер буфера для хранения имени
	GLuint bufferLength = GetActiveUniformMaxLength();
	if (!bufferLength)
	{
		// Нет активных uniform переменных
		return std::string();
	}
	std::vector<char> buffer(bufferLength);
	GLsizei nameLength = 0;

	// Получаем имя, тип и размер переменной
	GetActiveUniform(
		index, bufferLength, &nameLength, size, type, &buffer[0]);

	// Переводим их в строковое представление
	return std::string(&buffer[0], &buffer[nameLength]);
}

// Возвращаем максимальную длину для хранения имени 
	// attribute-переменной программы
GLuint CProgramBase::GetActiveAttributeMaxLength()const
{
	return GetParameterOfProgram(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
}

// Получаем информацию об имени, типе, длине и размере активной
	// attribute-переменной
void CProgramBase::GetActiveAttrib(
	GLuint index, GLsizei maxLength,
	GLsizei* length, GLint* size,
	GLenum* type, GLchar* name)const
{
	assert(m_program);
	assert(index < GetActiveAttributes());
	glGetActiveAttrib(m_program, index, maxLength, length, size, type, name);
}

// Получаем информацию об имени, размере и типе активной
	// attribute-переменной более простым способом
std::string CProgramBase::GetActiveAttrib(GLuint index, GLint* size, GLenum* type)const
{
	GLuint bufferLength = GetActiveAttributeMaxLength();
	if (!bufferLength)
	{
		// Нет активных attribute-переменных
		return std::string();
	}
	std::vector<char> buffer(bufferLength);
	GLsizei nameLength = 0;

	// Получаем имя, тип и размер переменной
	GetActiveAttrib(
		index, bufferLength,
		&nameLength, size,
		type, &buffer[0]);

	// Переводим их в строковое представление
	return std::string(&buffer[0], &buffer[nameLength]);
}

// Получаем параметр программного объекта
GLint CProgramBase::GetParameterOfProgram(GLenum pname)const
{
	GLint value = 0;
	GetParameterOfProgram(pname, &value);
	return value;
}

