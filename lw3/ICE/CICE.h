#pragma once
#include "CGLApplication.h"
#include <vector>

class CICE :
	public CGLApplication
{
public:
	CICE(const char* title, int width, int height);
	~CICE(void);
	void SetColor(float red, float green, float blue);
protected:
	// Перегружаем необходимые виртуальные методы родительского класса
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
private:
	static constexpr float M_PI = 3.1415926f;
	static void DrawLine(float x1, float y1, float x2, float y2);
	static void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
	static void DrawRectangle(float cx, float cy, float height, float width);
	static void DrawEllipse(
		float xCenter, float yCenter, float rx, float ry, int points = 360);
	static void DrawHalfEllipse(
		float xCenter, float yCenter, float rx, float ry, int points = 180); 
	static void DrawSparkPlug(float xStart, float yStart);
	static void DrawLeftValve(float xStart, float yStart);
	static void DrawRightValve(float xStart, float yStart);
	static void DrawPipeline(float xStart, float yStart);
	static void DrawHousingWall(float xStart, float yStart, bool isLeft); 
	static void DrawValveMechanism(float xStart, float yStart);
	static void DrawPiston(float xStart, float yStart);
	static void DrawHousing(float xStart, float yStart);
	static void DrawICE(float xCenter, float yCenter);
	static std::vector<float> m_color;
};
