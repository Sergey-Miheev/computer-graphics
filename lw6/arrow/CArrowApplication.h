#pragma once
#include <iostream>
#include "CGLApplication.h"
#include "CProgram.h"
#include "CShader.h"

class CArrowApplication :
    public CGLApplication
{
public:
	CArrowApplication(const char* title, int width, int height, GLuint program = 0);
    ~CArrowApplication();
protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
private:
	void InitShaders();

	// ”гол обзора по вертикали
	static const double FIELD_OF_VIEW;
	static const double ZNEAR;
	static const double ZFAR;

	CProgram m_program;
	CShader m_vertexShader;
	CShader m_fragmentShader;
	CShader m_geometryShader;
};