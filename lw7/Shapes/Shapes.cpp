#include <iostream>
#include <boost/interprocess/detail/atomic.hpp>
#include <SDL.h>
#include "CApplication.h"
/*
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
*/
#ifdef __cplusplus
extern "C"
#endif

int main(int /*argc*/, char* /*argv*/[])
{
	CApplication app;
	app.MainLoop();
	return 0;
}
