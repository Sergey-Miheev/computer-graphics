#include <iostream>
#include "CCanabolaApplication.h"

const char* TITLE = "Canabola";

const int width = 1300;

const int height = 750;

CCanabolaApplication canbolaApp(TITLE, width, height);

int main()
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}
    canbolaApp.MainLoop();

	return 0;
}