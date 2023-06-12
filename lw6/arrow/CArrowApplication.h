#pragma once
#include <iostream>
#include "CGLApplication.h"
#include "CProgramImpl.h"
#include "CShaderImpl.h"

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

	CProgram m_program;
	CShader m_vertexShader;
	CShader m_fragmentShader;
	CShader m_geometryShader;
};