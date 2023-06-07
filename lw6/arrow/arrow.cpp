#include <iostream>
#include "CArrowApplication.h"

const char* TITLE = "Arrow";

const int width = 1300;

const int height = 750;

CArrowApplication arrow(TITLE, width, height);

int main()
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}

	arrow.MainLoop();

	return 0;
}

// воспользоваться функцией atan2