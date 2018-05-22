
#include "PhilipsWave.h"
#include <cassert>
#include <complex>

typedef std::complex<double> dcomp;

PhilipsWave::PhilipsWave()
{
  amplitude = 1;
  direction = Dvector<double>(2, 2.0);
  frequence = 1;
}

PhilipsWave::PhilipsWave(double ampli, Dvector<double> dir, double freq)
{
  assert(dir.size() == 2);

  amplitude = ampli;
  direction = dir;
  frequence = freq;
}

PhilipsWave::PhilipsWave(const PhilipsWave & G)
{
    amplitude = G.amplitude;
    direction = Dvector<double>(G.direction);
    frequence = G.frequence;
}

void PhilipsWave::operator= (const PhilipsWave & G)
{
    amplitude = G.amplitude;
    direction = Dvector<double>(G.direction);
    frequence = G.frequence;
}

bool PhilipsWave::operator==(const PhilipsWave & G)
{
    return(amplitude == G.amplitude && direction == G.direction && frequence == G.frequence);
}

PhilipsWave::~PhilipsWave()
{
    //delete direction ?
}

double PhilipsWave::getAmplitude()
{
    return amplitude;
}
