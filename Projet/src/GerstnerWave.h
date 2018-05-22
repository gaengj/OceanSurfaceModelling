#ifndef GERSTNERWAVE_H
#define GERSTNERWAVE_H

#include "Dvector.h"

/*frequence^2 = g * direction.norm()
  On fera l’hypothèse que toutes les vagues ont une
  direction proche de la direction moyenne du vent (de WaveModel)
  Pour l’amplitude de chaque onde de Gerstner, on s’appliquera à ce que le ratio
  amplitude-longueur d’onde soit identique pour toutes les ondes.
  Enfin, en ce qui concerne la phase, nous pourrons la choisir constante pour
  l’ensemble des vagues.
*/
class GerstnerWave {

  /** ampli amplitude de la vague
   */
  double amplitude;
  /** phase de la vague
   */
  double phase;
  /** direction de la vague
   */
  Dvector<double> direction;
  /** fréquence de la vague
   */
  double frequence;

  public:
  GerstnerWave();
  GerstnerWave(double ampli, double phi, Dvector<double> dir, double freq);
  GerstnerWave(const GerstnerWave & G);
  void operator= (const GerstnerWave & G);
  bool operator==(const GerstnerWave & G);
  ~GerstnerWave();
  double operator() (int x, int y, int t) const;
};

template class Dvector<double>;

#endif
