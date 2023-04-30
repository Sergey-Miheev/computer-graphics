#include "CCube.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glut.h"

#pragma once
// ����� ���������, ���������� ������ ��� ��� ��������� � ����������
class CMaze
{
public:
	// �������� ���������
	CMaze(std::string mazeStructureFileName);
	// ������ ��������� �� ����� � ������
	void WriteMazeFromFileToArray(std::string mazeStructureFileName);
	// ������ ������������ ���
	void Draw(float = 32.0);
	// ������ ���� ���, �� ���� ���, �������, � �����, ���� ��� �������
	void DrawRow(float cx, float cy, float cz, float length, float width, float height);
	// ������ ���
	void DrawCube(float cx, float cy, float cz);
	// ��������� ��������� �� ��� � ������ ������� �������
	bool IsCube(int cZ, int cX);
private:
	// ��������� ��������� 
	std::vector<std::vector<char>> m_mazeStructure;
};
