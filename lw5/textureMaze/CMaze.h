#include "CCube.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "LoadTexture.h"
#include "GL/glut.h"

#pragma once
// ����� ���������, ���������� ������ ��� ��� ��������� � ����������
class CMaze
{
public:
	// �������� ���������
	CMaze(std::string mazeStructureFileName);
	// ������ ������������ ���
	const void Draw();
	// ��������� ��������� �� ��� � ������ ������� �������
	const bool IsDrawedCube(int cZ, int cX);
private:
	// ������ ��������� �� ����� � ������
	const void WriteMazeFromFileToArray(std::string mazeStructureFileName);
	// ��������� ��������
	const void LoadCubeTextures();
	// ������ ���� ���, �� ���� ���, �������, � �����, ���� ��� �������
	const void DrawRow(float cx, float cy, float cz, float length, float width, float height);
	// ������ ���
	const void DrawCube(float cx, float cy, float cz);
	// ��������� ��������� 
	std::vector<std::vector<char>> m_mazeStructure;
};














//// ����������� ������ ������� �� ���������� ���������� X
	//int CalculateIndexByCoordX(double ZNear);
	//// ����������� ������ ������� �� ���������� ���������� Z
	//int CalculateIndexByCoordZ(double ZNear);