#include <iostream>
#include "GL/glut.h"

#pragma once
class CCube
{
public:
	enum CubeSide
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
	void Draw();
	// ������ ���� ������� ����
	void SetSideColor(
		CubeSide side, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255);
private:
	float m_size;

	// ���������� ������� ������ ����� �������(0)
	float m_x;
	float m_y;
	float m_z;

	// ����� ������ ����
	GLubyte m_sideColors[6][4];
};
