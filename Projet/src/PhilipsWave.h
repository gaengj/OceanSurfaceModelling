#ifndef PHILIPSWAVE_H
#define PHILIPSWAVE_H

#include "Dvector.h"
#include "Height.h"

typedef std::complex<double> dcomp;

class PhilipsWave {
  double amplitude;
  Dvector<double> direction;
  double frequence;

  public:
  PhilipsWave();
  PhilipsWave(double ampli, Dvector<double> dir, double freq);
  PhilipsWave(const PhilipsWave & G);
  void operator= (const PhilipsWave & G);
  bool operator==(const PhilipsWave & G);
  ~PhilipsWave();
  double getAmplitude();
};

#endif
