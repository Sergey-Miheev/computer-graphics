#include "GL/glut.h"
#pragma once

// ����� �����������(������), ������� ����� "������������"
class CObserver
{
public:
	CObserver();
	~CObserver(void);

	// ���������� ���������� X �����������
	double GetCoordX();
	// ������������� ���������� X �����������
	void SetCoordX(double cX);
	// ���������� ���������� Y �����������
	double GetCoordY();	
	// ������������� ���������� Y �����������
	void SetCoordY(double cY);
	// ���������� ���������� Z �����������
	double GetCoordZ();
	// ������������� ���������� Z �����������
	void SetCoordZ(double cZ);
	
	// ���������� ���������� X ������� ����������� �����������
	double GetDirectionX();
	// ������������� ���������� X ������� ����������� �����������
	void SetDirectionX(double cX);

	// ���������� ���������� Z ������� ����������� �����������
	double GetDirectionZ();
	// ������������� ���������� Z ������� ����������� �����������
	void SetDirectionZ(double cZ);

	// ���������� ���� �������� �����������
	double GetAngle();
	// ������������� ���� �������� �����������
	void SetAngle(double angle);

	// ���������� �������� ��������� ����
	double GetAngleChangingSpeed();

	// ���������� �������� �����������
	double GetSpeed();
private:
	// ���������� �����������
	double m_X;
	double m_Y;
	double m_Z;

	// ������ ����������� �������� �����������
	double m_DirectionX;
	double m_DirectionZ;

	// ���� �������� �����������
	double m_Angle;

	// �������� ��������� ����
	double m_angleChangingSpeed;

	// �������� �������� �����������
	float m_Speed;
};

