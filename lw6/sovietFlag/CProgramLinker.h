#pragma once
#include <vector>
#include <GL/glut.h>

class CProgramLinker
{
public:
	CProgramLinker(void);
	~CProgramLinker(void);
	void LinkProgram(GLuint program);
	void CheckStatus();
private:
	std::vector<GLuint> m_programs;
};


