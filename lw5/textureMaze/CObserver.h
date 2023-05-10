#include "GL/glut.h"
#pragma once

// класс наблюдателя(камеры), который будет "перемещаться"
class CObserver
{
public:
	CObserver();
	~CObserver(void);

	// возвращает координату X наблюдателя
	double GetCoordX();
	// устанавливает координату X наблюдателя
	void SetCoordX(double cX);
	// возвращает координату Y наблюдателя
	double GetCoordY();	
	// устанавливает координату Y наблюдателя
	void SetCoordY(double cY);
	// возвращает координату Z наблюдателя
	double GetCoordZ();
	// устанавливает координату Z наблюдателя
	void SetCoordZ(double cZ);
	
	// возвращает координату X вектора направления наблюдателя
	double GetDirectionX();
	// устанавливает координату X вектора направления наблюдателя
	void SetDirectionX(double cX);

	// возвращает координату Z вектора направления наблюдателя
	double GetDirectionZ();
	// устанавливает координату Z вектора направления наблюдателя
	void SetDirectionZ(double cZ);

	// возвращает угол поворота наблюдателя
	double GetAngle();
	// устанавливает угол поворота наблюдателя
	void SetAngle(double angle);

	// возвращает скорость изменения угла
	double GetAngleChangingSpeed();

	// возвращает скорость наблюдателя
	double GetSpeed();
private:
	// координаты наблюдателя
	double m_X;
	double m_Y;
	double m_Z;

	// вектор направления движения наблюдателя
	double m_DirectionX;
	double m_DirectionZ;

	// угол поворота наблюдателя
	double m_Angle;

	// скорость изменения угла
	double m_angleChangingSpeed;

	// скорость движения наблюдателя
	float m_Speed;
};

