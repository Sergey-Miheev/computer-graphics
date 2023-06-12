#include "CShader.h"
#include <assert.h>

// Задаем исходный код шейдера
void CShaderBase::SetSource(GLsizei count, const GLchar** strings, const GLint* lengths)
{
	assert(m_shader != 0);

	glShaderSource(m_shader, count, strings, lengths);
}

// Задаем исходный код шейдера (в одной строке)
void CShaderBase::SetSource(const GLchar* source, GLint length)
{
	const GLchar** ppSource = &source;
	SetSource(1, ppSource, &length);
}

// Задаем исходный код шейдера (одна ASCIIZ-строка)
void CShaderBase::SetSource(const GLchar* source)
{
	const GLchar** ppSource = &source;
	SetSource(1, ppSource, NULL);
}

// Получаем значение некоторого параметра шейдера
void CShaderBase::GetParameter(GLenum pname, GLint* param)const
{
	assert(m_shader != 0);
	glGetShaderiv(m_shader, pname, param);
}

// Упрощенный вариант предыдущего метода
GLint CShaderBase::GetParameter(GLenum pname)const
{
	GLint value;
	GetParameter(pname, &value);
	return value;
}

// Получаем информационный лог от шейдера
void CShaderBase::GetInfoLog(GLsizei bufSize, GLsizei* length, GLchar* infoLog)const
{
	assert(m_shader != 0);
	glGetShaderInfoLog(m_shader, bufSize, length, infoLog);
}

// Получаем информационный лог от шейдера
	// (упрощенный вариант)
std::string CShaderBase::GetInfoLog()const
{
	GLint length = GetParameter(GL_INFO_LOG_LENGTH);
	if (length > 0)
	{
		std::vector<char> buffer(length);
		GetInfoLog(length, &length, &buffer[0]);
		std::string log(&buffer[0]);
		return log;
	}
	else
	{
		return std::string();
	}
}

// Получаем идентификатор шейдерного объекта
CShaderBase::operator GLuint()const
{
	return m_shader;
}

// Получаем идентификатор шейдерного объекта (альтернативный вариант)
GLuint CShaderBase::Get()const
{
	return m_shader;
}

// Компилируем ешйдер
void CShaderBase::Compile()
{
	assert(m_shader != 0);
	glCompileShader(m_shader);
}

// Присоединяем шейдерный объект к классу и возвращаем
	// дескриптор ранее присоединенного
GLuint CShaderBase::Attach(GLuint shader)
{
	GLuint tmp = m_shader;
	m_shader = shader;
	return tmp;
}

// Отсоединяем шейдерный объект
GLuint CShaderBase::Detach()
{
	return Attach(0);
}

// Удаляем шейдерный объект
void CShaderBase::Delete()
{
	assert(m_shader != 0);
	if (m_shader != 0)
	{
		glDeleteShader(Detach());
		m_shader = 0;
	}
}

