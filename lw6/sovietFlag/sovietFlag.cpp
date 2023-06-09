﻿#include <iostream>
#include "CFlagApplication.h"

const char * TITLE = "USSR Flag";

const int width = 1300;

const int height = 750;

CFlagApplication flagApp(TITLE, width, height);

int main()
{
	glewInit();
	if (!GLEW_ARB_shader_objects)
	{
		return -1;
	}

	flagApp.MainLoop();

	return 0;
}

