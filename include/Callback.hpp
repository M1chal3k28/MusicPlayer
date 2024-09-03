#pragma once 

#include <Config.hpp>
#include <FFT.hpp>

extern float output[];
extern float LastHeights[];

void callback(void * bufferData, unsigned int frames);