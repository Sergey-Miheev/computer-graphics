#include "CMazeApplication.h"

// ���������� �� ������� � ������� ���������� ���������
const double CMazeApplication::Z_NEAR = 0.01;
const double CMazeApplication::Z_FAR = 40;

#define M_PI 3.141592653589793

// ���� ������ �� ���������
const double CMazeApplication::FIELD_OF_VIEW = 60 * M_PI / 180.0;

CMazeApplication::CMazeApplication(const char* title, int width, int height, std::string mazeStructureFileName)
	: CGLApplication(title, width, height)
	, m_observer(CObserver())
	, m_maze(CMaze(mazeStructureFileName))
{
}

CMazeApplication::~CMazeApplication(void)
{
}

void CMazeApplication::OnInit()
{
	// � ���� ������� ������ �����
	glClearColor(1, 1, 1, 1);

	// �������� ����� ���������� ������
	glEnable(GL_CULL_FACE);
	// ��������������� ����� ��������� ������� ������
	glCullFace(GL_BACK);
	// ������� ��������� ��������� �������, ���� ��� �� ���������
	// ����� ������ �������������� ������ ������� �������
	glFrontFace(GL_CCW);

	// �������� ���� ������� ��� �������� ��������� ����� � ������������
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);        // ���������� ��������� ��������
}

void CMazeApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ��������� ��������� �������
	glLoadIdentity();

	CObserver observer = CObserver();

	const auto lookAtMat = glm::lookAt(
		glm::dvec3(m_observer.GetCoordX(), m_observer.GetCoordY(), m_observer.GetCoordZ()), // ��������� ������
		glm::dvec3(m_observer.GetCoordX() + m_observer.GetDirectionX(), m_observer.GetCoordY(), m_observer.GetCoordZ() + m_observer.GetDirectionZ()), // �����, � ������� ���������� ������
		glm::dvec3(0, 1, 0) // ����������� "�����"
	);
	glLoadMatrixd(&lookAtMat[0][0]);

	m_maze.Draw();
}

void CMazeApplication::OnReshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, width, height);

	// ��������� ����������� ������ ���������� ������� ����
	double aspectRatio = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const auto perspectiveMatrix = glm::perspective(FIELD_OF_VIEW, aspectRatio, Z_NEAR, Z_FAR);
	glLoadMatrixd(&perspectiveMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

void CMazeApplication::OnKeyboard(unsigned char key, int x, int y)
{
	int leftBorderZ = 0;
	int leftBorderX = 0;
	int rightBorderZ = 0;
	int rightBorderX = 0;
	int frontBorderZ = 0;
	int frontBorderX = 0;
	switch (key)
	{
	case 'w':
		// ���� ��� � -Z (��� 0) � +� (��� 0), ��������� ������������ ������ �� ������� �������
		if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// ���� ��� � +Z (��� 0) � +� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// ���� ��� � +Z (��� 0) � -� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// ���� ��� � -Z (��� 0) � -� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);			
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		
		// ���� �� �����-�� �� ���� ���, �� ���������
		if (m_maze.IsDrawedCube(leftBorderZ, leftBorderX) || m_maze.IsDrawedCube(rightBorderZ, rightBorderX) || m_maze.IsDrawedCube(frontBorderZ, frontBorderX))
		{
			break;
		}

		m_observer.SetCoordZ(m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed());
		m_observer.SetCoordX(m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed());
		break;		
	//���� ��� �����(� ��������������� ������� ����������� �������),
	case 's':
		// ���� ��� � +Z (��� 0) � -� (��� 0), ��������� ������������ ������ �� ������� �������
		if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// ���� ��� � -Z (��� 0) � -� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// ���� ��� � -Z (��� 0) � +� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// ���� ��� � +Z (��� 0) � +� (��� 0), ��������� ������������ ������ �� ������� �������
		else if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}

		// ���� �� �����-�� �� ���� ���, �� ���������
		if (m_maze.IsDrawedCube(leftBorderZ, leftBorderX) || m_maze.IsDrawedCube(rightBorderZ, rightBorderX) || m_maze.IsDrawedCube(frontBorderZ, frontBorderX))
		{
			break;
		}

		m_observer.SetCoordZ(m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed());
		m_observer.SetCoordX(m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed());
		break;
	case 'a':
		m_observer.SetAngle(m_observer.GetAngle() - m_observer.GetAngleChangingSpeed());
		m_observer.SetDirectionX(sin(m_observer.GetAngle()));
		m_observer.SetDirectionZ(-cos(m_observer.GetAngle()));
		break;
	case 'd':
		m_observer.SetAngle(m_observer.GetAngle() + m_observer.GetAngleChangingSpeed());
		m_observer.SetDirectionX(sin(m_observer.GetAngle()));
		m_observer.SetDirectionZ(-cos(m_observer.GetAngle()));
		break;
	case 'p':
		audiere::AudioDevicePtr device = audiere::OpenDevice(); // �������� AudioDevice 
		audiere::OutputStreamPtr sound = OpenSound(device, "../doom.wav", false); //������� ����� ��� �����
		sound->play(); //����������� ����
		char ch = _getche();
		break;
	}
}

void CMazeApplication::OnIdle()
{
	// ���������� ����������� ����
	PostRedisplay();
}