#include "CObserver.h"

CObserver::CObserver()
	: m_X(3)
	, m_Y(1)
	, m_Z(29)
	, m_Speed(0.1)
	, m_Angle(0.0)
	, m_DirectionX(0)
	, m_DirectionZ(-1)
{
}

CObserver::~CObserver(void)
{
}

// возвращает координату X наблюдателя
double CObserver::GetCoordX()
{
	return m_X;
}

// возвращает координату Y наблюдателя
double CObserver::GetCoordY()
{
	return m_Y;
}

// возвращает координату Z наблюдателя
double CObserver::GetCoordZ()
{
	return m_Z;
}

// устанавливает координату X наблюдателя
void CObserver::SetCoordX(double cX)
{
	m_X = cX;
}
// устанавливает координату Y наблюдателя
void CObserver::SetCoordY(double cY)
{
	m_Y = cY;
}
// устанавливает координату Z наблюдателя
void CObserver::SetCoordZ(double cZ)
{
	m_Z = cZ;
}

// возвращает координату X вектора направления наблюдателя
double CObserver::GetDirectionX()
{
	return m_DirectionX;
}
// устанавливает координату X вектора направления наблюдателя
void CObserver::SetDirectionX(double cX)
{
	m_DirectionX = cX;
}

// возвращает координату Z вектора направления наблюдателя
double CObserver::GetDirectionZ()
{
	return m_DirectionZ;
}
// устанавливает координату Z вектора направления наблюдателя
void CObserver::SetDirectionZ(double cZ)
{
	m_DirectionZ = cZ;
}

// возвращает угол поворота наблюдателя
double CObserver::GetAngle()
{
	return m_Angle;
}

// устанавливает угол поворота наблюдателя
void CObserver::SetAngle(double angle)
{
	m_Angle = angle;
}

// возвращает скорость наблюдателя
double CObserver::GetSpeed()
{
	return m_Speed;
}