#include <iostream>
#include "CMazeApplication.h"

CMazeApplication maze("Maze", 1200, 750, "maze.txt");

int main()
{
    maze.MainLoop();
}