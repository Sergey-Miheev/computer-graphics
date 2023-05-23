#pragma once
#include "CCube.h"
#include "Windows.h" 

// убрать CCube из хедера
// у функции нет константного контекста 
const bool LoadTexture(LPCWSTR filename, unsigned int num_tex);