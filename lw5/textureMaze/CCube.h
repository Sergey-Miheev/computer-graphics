#include <iostream>
#define GLEW_STATIC
#include <glew.h>
#pragma once
#include "GL/glut.h"

// ������ �������� ����� 
class CCube
{
public:
	const enum CubeSide
	{
		CS_NEGATIVE_X,
		CS_POSITIVE_X,
		CS_NEGATIVE_Y,
		CS_POSITIVE_Y,
		CS_NEGATIVE_Z,
		CS_POSITIVE_Z,

		CS_MIN_CUBE_SIDE_INDEX = CS_NEGATIVE_X,
		CS_MAX_CUBE_SIDE_INDEX = CS_POSITIVE_Z,
	};
public:
	// ������� ��� � �������� ������ �������, ������� ���������� ������� ������ ����� �������(0)
	CCube(float x, float y, float z, float size = 2);
	// ������ ���
	const void Draw();
private:
	const float m_size;

	// ���������� ������� ������ ����� �������(0)
	const float m_x;
	const float m_y;
	const float m_z;
};
