#ifndef WAVEMODEL_H
#define WAVEMODEL_H

#include "Dvector.h"

class WaveModel {
  protected:
  /** Vecteur de dim 2 correspondant à la direction du vent
  */
  Dvector<double> windDirection;
  /** Alignement moyen des vagues
  */
  double meanAlignment;
  /** Intensité
  */
  double intensity;
  /** Longueur d'onde moyenne des vagues
  */
  double meanWaveLength;
  /** Ajustement de la heuteur
  */
  double heightAjustment;

  public:
  WaveModel();
  WaveModel(const WaveModel & V);
  ~WaveModel();
  void operator= (const WaveModel &);

  Dvector<double> getWindDirection() const;
  double getMeanAlignment() const;
  double getIntensity() const;
  double getMeanWaveLength() const;
  double getHeightAjustment() const;

  virtual double operator() (int x, int y, int t) = 0;

};

#endif
