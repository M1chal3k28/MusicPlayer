#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

// https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
using namespace std;
using Complex = complex<double>;
using CArray = vector<Complex>;

void fft(CArray& x) {
    size_t N = x.size();
    if (N <= 1) return;

    // Devide signal to odd and even
    CArray even(N / 2);
    CArray odd(N / 2);
    for (size_t i = 0; i < N / 2; ++i) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    // Recursion
    fft(even);
    fft(odd);

    // Merge signal
    for (size_t k = 0; k < N / 2; ++k) {
        Complex t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

void computeFFT(float* samples, int fftSize, float* output) {
    // Prepare input buffer
    CArray data(fftSize);
    for (int i = 0; i < fftSize; ++i) {
        data[i] = Complex(samples[i], 0.0);
    }

    // Perform fft
    fft(data);

    // Calculate output
    for (int i = 0; i < fftSize / 2; ++i) {
        output[i] = abs(data[i]) / (fftSize / 2);
    }
}
