#include "conio.h"
#include "Windows.h" 
#include "audiere.h"
#include "CMaze.h"
#include "CObserver.h"
#include "CGLApplication.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#pragma once
class CMazeApplication : public CGLApplication
{
public:
	CMazeApplication(const char* title, int width, int height, std::string mazeStructureFileName);
	~CMazeApplication(void);
protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	virtual void OnIdle();
private:
	// Расстояние до ближней и дальней плоскостей отсечения
	static const double Z_NEAR;
	static const double Z_FAR;

	// Угол обзора по вертикали
	static const double FIELD_OF_VIEW;

	CObserver m_observer;

	CMaze m_maze;
};