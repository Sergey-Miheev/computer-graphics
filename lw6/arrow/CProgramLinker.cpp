#include "CProgramImpl.h"
#include "CProgramLinker.h"
#include <vector>
#include <sstream>

CProgramLinker::CProgramLinker(void)
{
}

CProgramLinker::~CProgramLinker(void)
{
}

void CProgramLinker::LinkProgram(GLuint program)
{
	// ��������� ��������� � ��������� �� � ������
	// ����������� ��������
	CProgramHandle prog(program);
	prog.LinkProgram();
	m_programs.push_back(program);
}

// ��������� ������ ���������������� ��������� ��������
void CProgramLinker::CheckStatus()
{
	std::stringstream strm;

	bool hasErrors = false;

	for (size_t i = 0; i < m_programs.size(); ++i)
	{
		CProgramHandle program(m_programs[i]);
		if (program.GetParameterOfProgram(GL_LINK_STATUS) != GL_TRUE)
		{
			hasErrors = true;
			strm << "Program " << program << " linkage failed: " <<
				program.GetInfoLogProgram() << "\n";
		}
	}

	m_programs.clear();

	if (hasErrors)
	{
		throw std::runtime_error(strm.str());
	}
}