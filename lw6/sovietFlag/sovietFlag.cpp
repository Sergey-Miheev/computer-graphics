#include <iostream>
#include "CFlagApplication.h"

const char * TITLE = "USSR";

const int width = 1200;

const int height = 900;

CFlagApplication flagApp(TITLE, width, height);

int main()
{
	flagApp.MainLoop();
}