#include <Callback.hpp>

float output[SIZE/2];
float LastHeights[SIZE/2];

void callback(void * bufferData, unsigned int frames) {
    float * buffer = (float *)bufferData;
    computeFFT(buffer, frames, output);
}