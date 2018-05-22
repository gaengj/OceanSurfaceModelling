/**
 * \file GerstnerWave.cxx
 * \brief Classe décrivant les caractéristiques d'une onde de Philips
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "GerstnerWave.h"
#include <math.h>
#include <cassert>

/** Constructeur par défaut, initialise la vague de Gerstner avec une amplitude,
 * une phase, et une fréquence égale à 1, et une direction égale à
 * Dvector<double>(2, 2)
 */
GerstnerWave::GerstnerWave()
{
  amplitude = 1;
  phase = 1;
  direction = Dvector<double>(2, 2);
  frequence = 1;
}

/** Constructeur d'initialisation
 * @param[in] ampli amplitude de la vague
 * @param[in] phi phase de la vague
 * @param[in] dir direction de la vague
 * @param[in] freq fréquence de la vague
 */
GerstnerWave::GerstnerWave(double ampli, double phi, Dvector<double> dir, double freq)
{
  assert(dir.size() == 2);


  //TODO:Relation Math à verifier sur les arguments avec try catch

  amplitude = ampli;
  phase = std::fmod(phi,2*M_PI);
  direction = dir;
  frequence = freq;
}

/** Constructeur par recopie
 */
GerstnerWave::GerstnerWave(const GerstnerWave & G)
{
    amplitude = G.amplitude;
    phase = G.phase;
    direction = Dvector<double>(G.direction);
    frequence = G.frequence;
}

/** Operateur d'affectation
 */
void GerstnerWave::operator= (const GerstnerWave & G)
{
    amplitude = G.amplitude;
    phase = G.phase;
    direction = Dvector<double>(G.direction);
    frequence = G.frequence;
}

/** Operateur d'égalité
 */
bool GerstnerWave::operator==(const GerstnerWave & G)
{
    return(amplitude == G.amplitude && phase == G.phase && direction == G.direction && frequence == G.frequence);
}

/** Destructeur
 */
GerstnerWave::~GerstnerWave()
{
    //delete direction ?
}

/** Opérateur d'accession, renvoit la hauteur d'une onde de Gerstner en un Point
 * de coordonées (x,y) à un instant t
 */
double GerstnerWave::operator() (int x, int y, int t) const
{
    return (amplitude * cos(direction(0)*x + direction(1)*y - frequence * t + phase));
}
