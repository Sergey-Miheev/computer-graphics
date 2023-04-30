#include "CCube.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glut.h"

#pragma once
// класс лабиринта, содержащий методы для его рисования и считывания
class CMaze
{
public:
	// Создание лабиринта
	CMaze(std::string mazeStructureFileName);
	// Запись лабиринта из файла в массив
	void WriteMazeFromFileToArray(std::string mazeStructureFileName);
	// Рисуем координатные оси
	void Draw(float = 32.0);
	// Рисуем один ряд, то есть пол, потолок, и стены, если они имеются
	void DrawRow(float cx, float cy, float cz, float length, float width, float height);
	// Рисуем куб
	void DrawCube(float cx, float cy, float cz);
	// проверяем находится ли куб в данной позиции массива
	bool IsCube(int cZ, int cX);
private:
	// Структура лабиринта 
	std::vector<std::vector<char>> m_mazeStructure;
};
