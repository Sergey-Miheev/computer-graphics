#include "CCube.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "LoadTexture.h"
#include "GL/glut.h"

#pragma once
// класс лабиринта, содержащий методы дл€ его рисовани€ и считывани€
class CMaze
{
public:
	// —оздание лабиринта
	CMaze(std::string mazeStructureFileName);
	// –исуем координатные оси
	const void Draw();
	// провер€ем находитс€ ли куб в данной позиции массива
	const bool IsDrawedCube(int cZ, int cX);
private:
	// «апись лабиринта из файла в массив
	const void WriteMazeFromFileToArray(std::string mazeStructureFileName);
	// «агружаем текстуры
	const void LoadCubeTextures();
	// –исуем один р€д, то есть пол, потолок, и стены, если они имеютс€
	const void DrawRow(float cx, float cy, float cz, float length, float width, float height);
	// –исуем куб
	const void DrawCube(float cx, float cy, float cz);
	// —труктура лабиринта 
	std::vector<std::vector<char>> m_mazeStructure;
};














//// высчитываем индекс массива по полученной координате X
	//int CalculateIndexByCoordX(double ZNear);
	//// высчитываем индекс массива по полученной координате Z
	//int CalculateIndexByCoordZ(double ZNear);