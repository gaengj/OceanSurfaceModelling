/**
 * \file fft.cxx
 * \brief Implémente la transformée de Fourier d'un vecteur et sa transformée
 * de Fourier inverse
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "fft.h"
#include <math.h>
#include <complex>
#include <cassert>

typedef std::complex<double> dcomp;

/** Renvoie la transformée de Fourier du vecteur passé en paramètre
 */
Dvector<dcomp> fft(Dvector<dcomp> &x){
	const dcomp J(0.0, 1.0);
	int n = x.size();

	/* On se limite au cas où n est une puissance de 2 */
	assert(log(n)/log(2.0) - floor(log(n)/log(2.0)) == 0.0);

	if (n <= 1){
		return x;
	}

	Dvector<dcomp> even;
	Dvector<dcomp> odd;

	for(int i=0; i<n; i++){
		if (i%2 == 0){
			even.resize(even.size()+1, x(i));
		} else {
			odd.resize(odd.size()+1, x(i));
		}
	}

	fft(even);
	fft(odd);

	for(int k=0; k<= n/2 -1; k++){
		dcomp t = odd(k) * exp(-2*M_PI*J*((double) k/n));
		x(k) = even(k) + t;
		x(k + n/2) = even(k) - t;
	}

	return x;
}

/** Renvoie la transformée de Fourier inverse du vecteur passé en paramètre
 */
Dvector<dcomp> ifft(Dvector<dcomp> &x){
	const dcomp J(0.0, 1.0);
	int n = x.size();

	/* On se limite au cas où n est une puissance de 2 */
	assert(log(n)/log(2.0) - floor(log(n)/log(2.0)) == 0.0);

	if (n <= 1){
		return x;
	}

	x = x.conjugue();
	fft(x);
	x /= n;
	x = x.conjugue();

	return x;
}

Dvector<double> ifftDouble(Dvector<dcomp> &x){
	const dcomp J(0.0, 1.0);
	int n = x.size();

	/* On se limite au cas où n est une puissance de 2 */
	assert(log(n)/log(2.0) - floor(log(n)/log(2.0)) == 0.0);

	if (n <= 1){
		Dvector<double> y = Dvector<double>(x.size(), 0);
		for(int i = 0; i<x.size(); i++){
				y(i) = abs(x(i));
		}
		return y;
	}

	x = x.conjugue();
	fft(x);
	x /= n;
	x = x.conjugue();
	Dvector<double> y = Dvector<double>(x.size(), 0);
  for(int i = 0; i<x.size(); i++){
		  y(i) = abs(x(i));
	}
	return y;
}
