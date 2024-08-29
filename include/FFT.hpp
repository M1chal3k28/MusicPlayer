#pragma once
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
using Complex = complex<double>;
using CArray = vector<Complex>;

void fft(CArray& x);
void computeFFT(float* samples, int fftSize, float* output);