#include "CMaze.h"

CMaze::CMaze(std::string mazeStructureFileName)
{
	WriteMazeFromFileToArray(mazeStructureFileName);
	LoadCubeTextures();
}

// ������ ��������� �� ����� � ������
const void CMaze::WriteMazeFromFileToArray(std::string mazeStructureFileName)
{
	// ������ ����� ��� ������ �� �������� ����� 
	std::ifstream mazeStructureStream(mazeStructureFileName);
	// ��������, �������� �� ������� ����
	if (!mazeStructureStream.is_open())
	{
		throw("Failed to open file");
		return;
	}

	std::string line = "";
	size_t vectorSize = 0;
	while (getline(mazeStructureStream, line))
	{

		m_mazeStructure.push_back(std::vector<char>());
		std::stringstream charsLineStream(line);
		char c;
		while (charsLineStream >> c)
		{
			m_mazeStructure[vectorSize].push_back(c);
		}
		vectorSize++;
	}
}

// ��������� ��������
const void CMaze::LoadCubeTextures()
{
	//��� ����
	LoadTexture(L"textures/stena1.bmp", 1);
	LoadTexture(L"textures/stena2.bmp", 2);
	// �������
	LoadTexture(L"textures/potolok.bmp", 3);
	// ���
	LoadTexture(L"textures/pol.bmp", 4);
	LoadTexture(L"textures/stena3.bmp", 5);
	LoadTexture(L"textures/stena4.bmp", 6);
}

const void CMaze::DrawRow(float cx, float cy, float cz, float width, float length, float height)
{
	glBegin(GL_QUADS);
	glVertex3f(cx, cy, cz);
	glVertex3f(cx, cy + height, cz);
	glVertex3f(cx + length, cy + height, cz + width);
	glVertex3f(cx + length, cy, cz + width);
	glEnd();
}

const void CMaze::DrawCube(float cx, float cy, float cz)
{
	CCube cube = CCube(cx, cy, cz);
	cube.Draw();
}

const void CMaze::Draw()
{	
	const float y = 0;
	const float cubeSize = 2;
	int z = 0;
	for (size_t row = 0; row < m_mazeStructure.size(); row++)
	{
		std::vector<char> line = m_mazeStructure[row];
		int x = 0;
		for (size_t column = 0; column < m_mazeStructure.size(); column++)
		{
			// ���� �����, ������ �
			if (line[column] == '#')
			{
				DrawCube(x, y, z);
			}
			// ���
			DrawCube(x, y - cubeSize, z);
			// �������
			DrawCube(x, y + cubeSize, z);
			x += 2;
		}
		z += 2;
	}
}

// ��������� ��������� �� ��� � ������ ������� �������
const bool CMaze::IsDrawedCube(int cZ, int cX)
{
	if (m_mazeStructure[cZ][cX] == '#')
	{
		return true;
	}
	return false;
}















/*
// ����������� ������ ������� �� ���������� ���������� X
int CMaze::CalculateIndexByCoordX(double ZNear)
{
	return floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + ZNear * 6) / 2)
}
*/