#include "CTextureCube.h"
#include "CTexture2D.cpp"
#include "CVector3.h"
#include <GL/glut.h>

template <bool t_managed, class TBase>
class CTextureImpl : public TBase
{
public:
	CTextureImpl<t_managed, TBase>(GLuint texture = 0)
		:TBase(texture)
	{
	}

	~CTextureImpl<t_managed, TBase>()
	{
		bool m = t_managed;
		if (m && (*this != 0))
		{
			Delete();
		}
	}

	// Присоединяем текстурный объект к экземпляру класса
	void Attach(GLuint texture)
	{
		if (t_managed && *this != 0)
		{
			Delete();
		}
		SetTexture(texture);
	}

};


class CTexturedCube
{
public:
	CTexturedCube();
	void Draw(GLfloat size = 1)const;
	void SetTextures(
		GLuint leftTexture, GLuint rightTexture,
		GLuint bottomTexture, GLuint topTexture,
		GLuint backTexture, GLuint frontTexture
	);
private:
	CTexture2D m_backTexture;
	CTexture2D m_frontTexture;
	CTexture2D m_leftTexture;
	CTexture2D m_rightTexture;
	CTexture2D m_bottomTexture;
	CTexture2D m_topTexture;
};
CTexturedCube::CTexturedCube(void)
{
}

void CTexturedCube::Draw(GLfloat size)const
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
	  /    /|
	 /    / |
	7----6  |
	|  0 |  1
	|    | /
	|    |/
	4----5
	*/

	// Массив координат вершин
	static const float vertices[8][3] =
	{
		{-1, -1, -1},	// 0
		{+1, -1, -1},	// 1
		{+1, +1, -1},	// 2
		{-1, +1, -1},	// 3
		{-1, -1, +1},	// 4
		{+1, -1, +1},	// 5
		{+1, +1, +1},	// 6
		{-1, +1, +1},	// 7
	};

	struct CubeFace
	{
		unsigned char vertex0;
		unsigned char vertex1;
		unsigned char vertex2;
		unsigned char vertex3;
		GLfloat tex0s, tex0t;
		GLfloat tex1s, tex1t;
		GLfloat tex2s, tex2t;
		GLfloat tex3s, tex3t;
		CTexture2D const& texture;
	};


	// Массив координат граней (в порядке, совпадающем с 
	// порядком объявления их в массиве цветов)
	// индексы вершин граней перечисляются в порядке их обхода
	// против часовой стрелки (если смотреть на грань снаружи)
	static const CubeFace faces[] =
	{
		{4, 7, 3, 0, 0, 1, 0, 0, 1, 0, 1, 1, m_leftTexture},	// грань x<0
		{5, 1, 2, 6, 1, 1, 0, 1, 0, 0, 1, 0, m_rightTexture},	// грань x>0
		{4, 0, 1, 5, 0, 1, 0, 0, 1, 0, 1, 1, m_bottomTexture},	// грань y<0
		{7, 6, 2, 3, 0, 0, 1, 0, 1, 1, 0, 1, m_topTexture},		// грань y>0
		{0, 3, 2, 1, 0, 1, 0, 0, 1, 0, 1, 1, m_frontTexture},	// грань z<0
		{4, 5, 6, 7, 0, 0, 1, 0, 1, 1, 0, 1, m_backTexture},	// грань z>0
	};
	static unsigned const faceCount = sizeof(faces) / sizeof(*faces);

	for (unsigned faceIndex = 0; faceIndex < faceCount; ++faceIndex)
	{
		CubeFace const& face = faces[faceIndex];

		face.texture.Bind();

		// Рисуем 4 вершины квадрата
		glBegin(GL_QUADS);
		{
			glTexCoord2f(face.tex0s, face.tex0t);
			CVector3f v0(vertices[face.vertex0]);
			v0 *= size;
			glVertex3fv(v0);

			glTexCoord2f(face.tex1s, face.tex1t);
			CVector3f v1(vertices[face.vertex1]);
			v1 *= size;
			glVertex3fv(v1);

			glTexCoord2f(face.tex2s, face.tex2t);
			CVector3f v2(vertices[face.vertex2]);
			v2 *= size;
			glVertex3fv(v2);

			glTexCoord2f(face.tex3s, face.tex3t);
			CVector3f v3(vertices[face.vertex3]);
			v3 *= size;
			glVertex3fv(v3);
		}
		glEnd();
	}
}

void CTexturedCube::SetTextures(
	GLuint leftTexture, GLuint rightTexture,
	GLuint bottomTexture, GLuint topTexture,
	GLuint backTexture, GLuint frontTexture
)
{
	// илициализируем текстурные объекты, соответствующие 6 сторонам куба
	m_leftTexture.Attach(leftTexture);
	m_rightTexture.Attach(rightTexture);
	m_bottomTexture.Attach(bottomTexture);
	m_topTexture.Attach(topTexture);
	m_backTexture.Attach(backTexture);
	m_frontTexture.Attach(frontTexture);
}
