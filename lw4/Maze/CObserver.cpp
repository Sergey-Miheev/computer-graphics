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

// ���������� ���������� X �����������
double CObserver::GetCoordX()
{
	return m_X;
}

// ���������� ���������� Y �����������
double CObserver::GetCoordY()
{
	return m_Y;
}

// ���������� ���������� Z �����������
double CObserver::GetCoordZ()
{
	return m_Z;
}

// ������������� ���������� X �����������
void CObserver::SetCoordX(double cX)
{
	m_X = cX;
}
// ������������� ���������� Y �����������
void CObserver::SetCoordY(double cY)
{
	m_Y = cY;
}
// ������������� ���������� Z �����������
void CObserver::SetCoordZ(double cZ)
{
	m_Z = cZ;
}

// ���������� ���������� X ������� ����������� �����������
double CObserver::GetDirectionX()
{
	return m_DirectionX;
}
// ������������� ���������� X ������� ����������� �����������
void CObserver::SetDirectionX(double cX)
{
	m_DirectionX = cX;
}

// ���������� ���������� Z ������� ����������� �����������
double CObserver::GetDirectionZ()
{
	return m_DirectionZ;
}
// ������������� ���������� Z ������� ����������� �����������
void CObserver::SetDirectionZ(double cZ)
{
	m_DirectionZ = cZ;
}

// ���������� ���� �������� �����������
double CObserver::GetAngle()
{
	return m_Angle;
}

// ������������� ���� �������� �����������
void CObserver::SetAngle(double angle)
{
	m_Angle = angle;
}

// ���������� �������� �����������
double CObserver::GetSpeed()
{
	return m_Speed;
}