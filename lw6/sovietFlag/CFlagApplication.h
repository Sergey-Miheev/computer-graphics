#pragma once
#include <iostream>
#include "CGLApplication.h"
#include "CProgram.cpp"

class CFlagApplication :
    public CGLApplication
{
public:
	CFlagApplication(const char* title, int width, int height, GLuint program = 0);
    ~CFlagApplication();
protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
private:
	void InitShaders();
	//void PrintProgramInfo(GLuint programId);
	CProgram m_program;

	//GLint m_twistLocation;
};

