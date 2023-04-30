#include "CICE.h"

std::vector<float> CICE::m_color;

CICE::CICE(const char* title, int width, int height)
	:CGLApplication(title, width, height, true)
{
}

CICE::~CICE() 
{
}

void CICE::SetColor(float red, float green, float blue)
{
	CICE::m_color = { red, green, blue };
}

void CICE::OnInit()
{
	// Задаем цвет очистки буфера кадра
	glClearColor(1, 1, 1, 1);
}

void CICE::OnDisplay()
{
	// Очищаем буфер цвета и буфер глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetColor(0.1, 0.8, 0);
	// Рисуем ДВС 1
	DrawICE(-0.6, 0.3);
	
	glScalef(0.7, 0.7, 1);

	SetColor(0.1, 0, 0.8);
	// Рисуем ДВС 2
	DrawICE(0.6, 0.3);
}

void CICE::OnReshape(int width, int height)
{
	// Настраиваем порт просмотра
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Делаем текущей матрицу проецирования и настраиваем ее параметры
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	const double aspectRatio = double(width) / double(height);
	double viewWidth = 1.0;
	double viewHeight = viewWidth;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}

	glOrtho(-viewWidth , viewWidth , -viewHeight , viewHeight , -1.0, 1.0);
	// Делаем текущей матрицей матрицу моделирования-вида
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void CICE::DrawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void CICE::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void CICE::DrawRectangle(float cx, float cy, float height, float width)
{
	glBegin(GL_QUADS);
	glVertex2f(cx, cy);
	glVertex2f(cx + width, cy);
	glVertex2f(cx + width, cy - height);
	glVertex2f(cx, cy - height);
	glEnd();
}

void CICE::DrawEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount)
{
	const float pi = 3.1415926f;
	const float step = float(2 * pi) / pointCount;

	// Эллипс представлет в виде "веера" из треугольников
	glBegin(GL_TRIANGLE_FAN);
	// Начальная точка веера располагается в центре эллипса
	glVertex2f(xCenter, yCenter);
	// Остальные точки - равномерно по его границе
	for (float angle = 0; angle <= float(2 * pi); angle += step)
	{
		float a = (fabsf(angle - float(2 * pi)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void CICE::DrawHalfEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount)
{
	const float pi = 3.1415926f;
	const float step = float(pi) / pointCount;

	// Эллипс представлет в виде "веера" из треугольников
	glBegin(GL_TRIANGLE_FAN);
	// Начальная точка веера располагается в центре эллипса
	glVertex2f(xCenter, yCenter);
	// Остальные точки - равномерно по его границе
	for (float angle = 0; angle <= float(pi); angle += step)
	{
		float a = (fabsf(angle + float(pi)) < 0.00001f) ? 0.f : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

// свеча
void CICE::DrawSparkPlug(float xStart, float yStart)
{
	glColor3f(0, 0, 0);
	DrawTriangle(xStart - 0.022, yStart-0.002, xStart + 0.065, yStart - 0.087, xStart + 0.138, yStart - 0.002);

	glColor3f(1, 1, 1);
	DrawRectangle(xStart + 0.023, yStart + 0.001, 0.06, 0.075);

	glColor3f(0, 0, 0);
	glLineWidth(2);
	DrawLine(xStart + 0.047, yStart - 0.046, xStart + 0.047, yStart);
	DrawLine(xStart + 0.073, yStart - 0.046, xStart + 0.073, yStart);

	DrawLine(xStart + 0.023, yStart - 0.001, xStart + 0.098, yStart - 0.001);

	DrawLine(xStart + 0.02, yStart + 0.05, xStart + 0.02, yStart);
	DrawLine(xStart + 0.1, yStart + 0.05, xStart + 0.1, yStart);
	DrawLine(xStart + 0.020, yStart + 0.05, xStart + 0.040, yStart + 0.05);
	DrawLine(xStart + 0.080, yStart + 0.05, xStart + 0.1, yStart + 0.05);
	DrawLine(xStart + 0.037, yStart + 0.05, xStart + 0.037, yStart + 0.11);
	DrawLine(xStart + 0.082, yStart + 0.05, xStart + 0.082, yStart + 0.11);
	DrawLine(xStart + 0.037, yStart + 0.11, xStart + 0.084, yStart + 0.11);
	DrawLine(xStart + 0.059, yStart + 0.11, xStart + 0.059, yStart + 0.16);
	DrawLine(xStart + 0.044, yStart - 0.086, xStart + 0.044, yStart -0.115);
	DrawLine(xStart + 0.044, yStart - 0.115, xStart + 0.074, yStart - 0.115);
	glLineWidth(3);
	DrawLine(xStart + 0.060, yStart - 0.086, xStart + 0.060, yStart - 0.105);

	glColor3f(0.3, 0.3, 0.3);
	DrawRectangle(xStart + 0.02, yStart - 0.048, 0.04, 0.08);	
}

// левый клапан
void CICE::DrawLeftValve(float xStart, float yStart)
{
	glLineWidth(3.50);
	DrawLine(xStart, yStart, xStart + 0.17, yStart - 0.16);

	DrawLine(xStart + 0.121, yStart - 0.205, xStart + 0.22, yStart - 0.115);
}

// правый клапан
void CICE::DrawRightValve(float xStart, float yStart)
{
	glLineWidth(3.50);
	DrawLine(xStart, yStart, xStart - 0.18, yStart - 0.17);

	DrawLine(xStart - 0.131, yStart - 0.215, xStart - 0.23, yStart - 0.125);
}

// трубопровод
void CICE::DrawPipeline(float xStart, float yStart)
{
	glColor3f(0.1, 0.1, 0.1);
	glLineWidth(1.5);
	DrawLine(xStart, yStart, xStart + 0.25, yStart);
	DrawLine(xStart + 0.55, yStart, xStart + 0.8, yStart);

	DrawLine(xStart, yStart + 0.1, xStart + 0.8, yStart + 0.1);

	glColor3f(m_color[0], m_color[1], m_color[2]);
	DrawHalfEllipse(xStart + 0.4, yStart + 0.1, 0.178, 0.086);
}

// стенка корпуса
void CICE::DrawHousingWall(float xStart, float yStart, bool isLeft)
{
	float height = 0.05;
	float width = 0.10;
	float heightDifference = 0.02;
	float shift = 0;
	if (isLeft)
	{
		shift = width / 2;
	}
	
	DrawRectangle(xStart, yStart, height * 1, width);
	for (int groove = 0; groove < 9; groove++)
	{
		yStart += height;
		DrawRectangle(xStart, yStart, height, width);
		yStart += height - heightDifference;
		DrawRectangle(xStart + shift, yStart, height, width / 2);
	}
	yStart += height;
	DrawRectangle(xStart, yStart, height * 2, width);
}

// клапанный механизм
void CICE::DrawValveMechanism(float xStart, float yStart)
{
	DrawPipeline(xStart - 0.4, yStart);

	DrawLeftValve(xStart - 0.25, yStart + 0.2);

	DrawRightValve(xStart + 0.28, yStart + 0.22);

	DrawSparkPlug(xStart - 0.06, yStart + 0.185);
}

// корпус
void CICE::DrawHousing(float xStart, float yStart)
{
	glColor3f(CICE::m_color[0], CICE::m_color[1], CICE::m_color[2]);
	DrawEllipse(xStart, yStart+0.096, 0.35, 0.35);
	DrawHousingWall(xStart - 0.252, yStart + 0.39, true);
	DrawHousingWall(xStart + 0.152, yStart + 0.39, false);

	glColor3f(1, 1, 1);
	DrawEllipse(xStart, yStart + 0.096, 0.29, 0.29);
	DrawRectangle(xStart - 0.152, yStart + 0.61, 0.49, 0.303);
}

// поршень
void CICE::DrawPiston(float xStart, float yStart)
{
	glColor3f(0.85, 0.85, 0.85);
	DrawEllipse(xStart, yStart, 0.1, 0.1);
	glColor3f(0.75, 0.75, 0.75);
	DrawEllipse(xStart, yStart, 0.03, 0.03);
	
	DrawRectangle(xStart - 0.14, yStart + 0.83, 0.32, 0.28);
	glColor3f(0, 0, 0);
	glLineWidth(2);
	
	DrawLine(xStart - 0.15, yStart + 0.7, xStart + 0.155, yStart + 0.7);
	DrawLine(xStart - 0.15, yStart + 0.73, xStart + 0.155, yStart + 0.73);
	DrawLine(xStart - 0.15, yStart + 0.76, xStart + 0.155, yStart + 0.76);

	glColor3f(0.3, 0.3, 0.3);
	
	// рычаг
	glBegin(GL_POLYGON);
		// левый нижний угол рычага
		glVertex2f(xStart + 0.065, yStart + 0.095);
		// вверх
		glVertex2f(xStart - 0.04, yStart + 0.51);
		// направо
		glVertex2f(xStart + 0.04, yStart + 0.51);
		// вниз
		glVertex2f(xStart + 0.115, yStart + 0.11);
	glEnd();
	
	// шестерёнка
	glBegin(GL_POLYGON);
		// левый верхний угол шестерёнки
		glVertex2f(xStart + 0.015, yStart + 0.055);
		// до рычага
		glVertex2f(xStart + 0.059, yStart + 0.10);
		// конец рычага
		glVertex2f(xStart + 0.118, yStart + 0.12);
		// направо
		glVertex2f(xStart + 0.175, yStart + 0.108);
		// вниз
		glVertex2f(xStart + 0.205, yStart + 0.02);
		// налево
		glVertex2f(xStart + 0.136, yStart - 0.032);
		// налево
		glVertex2f(xStart + 0.045, yStart - 0.035);
	glEnd();

	glColor3f(0.75, 0.75, 0.75);
	DrawEllipse(xStart + 0.11, yStart + 0.042, 0.050, 0.050);
}

void CICE::DrawICE(float xCenter, float yCenter)
{
	DrawValveMechanism(xCenter, yCenter+0.3);

	DrawHousing(xCenter, yCenter - 0.86);

	DrawPiston(xCenter, yCenter - 0.76);
}