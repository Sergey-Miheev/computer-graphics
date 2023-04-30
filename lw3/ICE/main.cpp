#include "CICE.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGTH = 700;
const char WINDOW_TITLE[] = "Internal Combustion Engine";
// при ресайзе пропорционально изменяялся
// Создаем экземпляр приложения
CICE app(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGTH);

int main(int argc, char* argv[])
{
	// и запускаем его
	app.MainLoop();

	return 0;
}