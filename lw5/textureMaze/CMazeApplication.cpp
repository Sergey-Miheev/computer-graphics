#include "CMazeApplication.h"

// Расстояние до ближней и дальней плоскостей отсечения
const double CMazeApplication::Z_NEAR = 0.01;
const double CMazeApplication::Z_FAR = 40;

#define M_PI 3.141592653589793

// Угол обзора по вертикали
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
	// И цвет очистки буфера цвета
	glClearColor(1, 1, 1, 1);

	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);        // Разрешение наложение текстуры
}

void CMazeApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Загружаем единичную матрицу
	glLoadIdentity();

	CObserver observer = CObserver();

	const auto lookAtMat = glm::lookAt(
		glm::dvec3(m_observer.GetCoordX(), m_observer.GetCoordY(), m_observer.GetCoordZ()), // Положение камеры
		glm::dvec3(m_observer.GetCoordX() + m_observer.GetDirectionX(), m_observer.GetCoordY(), m_observer.GetCoordZ() + m_observer.GetDirectionZ()), // Точка, в которую направлена камера
		glm::dvec3(0, 1, 0) // Направление "вверх"
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

	// Вычисляем соотношение сторон клиентской области окна
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
		// если идём в -Z (или 0) и +Х (или 0), проверяем пространство вокруг на наличие преград
		if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// если идём в +Z (или 0) и +Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// если идём в +Z (или 0) и -Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// если идём в -Z (или 0) и -Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);			
			rightBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		
		// если на каком-то из мест куб, не двигаемся
		if (m_maze.IsDrawedCube(leftBorderZ, leftBorderX) || m_maze.IsDrawedCube(rightBorderZ, rightBorderX) || m_maze.IsDrawedCube(frontBorderZ, frontBorderX))
		{
			break;
		}

		m_observer.SetCoordZ(m_observer.GetCoordZ() + m_observer.GetDirectionZ() * m_observer.GetSpeed());
		m_observer.SetCoordX(m_observer.GetCoordX() + m_observer.GetDirectionX() * m_observer.GetSpeed());
		break;		
	//если идём назад(в противоположной вектору направления стороне),
	case 's':
		// если идём в +Z (или 0) и -Х (или 0), проверяем пространство вокруг на наличие преград
		if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// если идём в -Z (или 0) и -Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() >= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
		}
		// если идём в -Z (или 0) и +Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() >= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}
		// если идём в +Z (или 0) и +Х (или 0), проверяем пространство вокруг на наличие преград
		else if (m_observer.GetDirectionZ() <= 0 && m_observer.GetDirectionX() <= 0)
		{
			leftBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			rightBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			leftBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			rightBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() - Z_NEAR * 6) / 2);
			frontBorderZ = floor((m_observer.GetCoordZ() - m_observer.GetDirectionZ() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
			frontBorderX = floor((m_observer.GetCoordX() - m_observer.GetDirectionX() * m_observer.GetSpeed() + Z_NEAR * 6) / 2);
		}

		// если на каком-то из мест куб, не двигаемся
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
		audiere::AudioDevicePtr device = audiere::OpenDevice(); // открывем AudioDevice 
		audiere::OutputStreamPtr sound = OpenSound(device, "../doom.wav", false); //создаем поток для звука
		sound->play(); //проигрываем звук
		char ch = _getche();
		break;
	}
}

void CMazeApplication::OnIdle()
{
	// Инициируем перерисовку окна
	PostRedisplay();
}