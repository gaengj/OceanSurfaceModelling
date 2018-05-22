#ifndef FFT_H
#define FFT_H

#include "Dvector.h"

typedef std::complex<double> dcomp;

Dvector<dcomp> fft(Dvector<dcomp> &x);
Dvector<dcomp> ifft(Dvector<dcomp> &x);
Dvector<double> ifftDouble(Dvector<dcomp> &x);
#endif
