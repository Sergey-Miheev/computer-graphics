#include "CMaze.h"

CMaze::CMaze(std::string mazeStructureFileName)
{
	WriteMazeFromFileToArray(mazeStructureFileName);
}

// Запись лабиринта из файла в массив
void CMaze::WriteMazeFromFileToArray(std::string mazeStructureFileName)
{
	// Создаём поток для чтения из входного файла 
	std::ifstream mazeStructureStream(mazeStructureFileName);
	// Проверем, открылся ли входной файл
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

void CMaze::DrawRow(float cx, float cy, float cz, float width, float length, float height)
{
	glBegin(GL_QUADS);
	glVertex3f(cx, cy, cz);
	glVertex3f(cx, cy + height, cz);
	glVertex3f(cx + length, cy + height, cz + width);
	glVertex3f(cx + length, cy, cz + width);
	glEnd();
}

void CMaze::DrawCube(float cx, float cy, float cz)
{
	CCube cube = CCube(cx, cy, cz);
	cube.SetSideColor(CCube::CS_NEGATIVE_X, 255, 0, 0);
	cube.SetSideColor(CCube::CS_POSITIVE_X, 0, 255, 0);
	cube.SetSideColor(CCube::CS_NEGATIVE_Y, 0, 0, 255);
	cube.SetSideColor(CCube::CS_POSITIVE_Y, 255, 255, 0);
	cube.SetSideColor(CCube::CS_NEGATIVE_Z, 0, 255, 255);
	cube.SetSideColor(CCube::CS_POSITIVE_Z, 255, 0, 255);
	cube.Draw();
}

void CMaze::Draw(float size)
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
			// если стена, рисуем её
			if (line[column] == '#')
			{
				DrawCube(x, y, z);
			}
			// пол
			DrawCube(x, y - cubeSize, z);
			// потолок
			DrawCube(x, y + cubeSize, z);
			x += 2;
		}
		z += 2;
	}
}

// проверяем находится ли куб в данной позиции массива
bool CMaze::IsCube(int cZ, int cX)
{
	if (m_mazeStructure[cZ][cX] == '#')
	{
		return true;
	}
	return false;
}
