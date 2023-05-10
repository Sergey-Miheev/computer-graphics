#include "CCube.h"

CCube::CCube(float x, float y, float z, float size)
	: m_x(x)
	, m_y(y)
	, m_z(z)
	, m_size(size)
{
}

const void CCube::Draw()
{
	/*

	   Y
	   |
	   |
	   |
	   +---X
	  /
	 /
	Z
	   3----2
	  /|   /|
	 / |  / |
	7----6  |
	|  0-|--1
	| /  | /
	|/   |/
	4----5

	{-1, -1, -1},	// 0
	{+1, -1, -1},	// 1
	{+1, +1, -1},	// 2
	{-1, +1, -1},	// 3
	{-1, -1, +1},	// 4
	{+1, -1, +1},	// 5
	{+1, +1, +1},	// 6
	{-1, +1, +1},	// 7

	*/
	// ������ ��������� ������
	float vertices[8][3] =
	{
		{m_x, m_y, m_z},							// 0
		{m_x + m_size, m_y, m_z},					// 1
		{m_x + m_size, m_y + m_size, m_z},			// 2
		{m_x, m_y + m_size, m_z},					// 3
		{m_x, m_y, m_z + m_size},					// 4
		{m_x + m_size, m_y, m_z + m_size},			// 5
		{m_x + m_size, m_y + m_size, m_z + m_size},	// 6
		{m_x, m_y + m_size, m_z + m_size},			// 7
	};

	// ������ ��������� ������ (� �������, ����������� � 
	// �������� ���������� �� � ������� ������)
	// ������� ������ ������ ������������� � ������� �� ������
	// ������ ������� ������� (���� �������� �� ����� �������)
	static const unsigned char faces[6][4] =
	{
		{0, 4, 7, 3},	// ����� x<0
		{5, 1, 2, 6},	// ����� x>0
		{0, 1, 5, 4},	// ����� y<0
		{7, 6, 2, 3},	// ����� y>0
		{1, 0, 3, 2},	// ����� z<0
		{4, 5, 6, 7},	// ����� z>0
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	// ������ ��������� ������ ������� 
	float textVertices[4][2] =
	{
		{0.0f, 0.0f},		// 0
		{1.0f, 0.0f},		// 1
		{1.0f, 1.0f},		// 2
		{0.0f, 1.0f},		// 3
	};

	for (size_t face = 0; face < faceCount; ++face)
	{
		glBindTexture(GL_TEXTURE_2D, face + 1);
		glBegin(GL_QUADS);
		{
			// ������ ��������������� �����, ���������� �� �������
			for (size_t i = 0; i < 4; ++i)
			{
				glTexCoord2fv(textVertices[i]);
				size_t vertexIndex = faces[face][i];
				glVertex3fv(vertices[vertexIndex]);
			}
		}
		glEnd();
	}
}
