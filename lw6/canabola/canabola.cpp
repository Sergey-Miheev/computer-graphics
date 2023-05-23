#include <iostream>
#include "CCanabolaApplication.h"

const char* TITLE = "Canabola";

const int width = 1200;

const int height = 900;

CCanabolaApplication canbolaApp(TITLE, width, height);

int main()
{
    canbolaApp.MainLoop();
}