/**
 * \file main.cxx
 * \brief Point d'entree du programme, lance la simulation
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

#include "window.hxx"
#include "Ocean.h"
#include "Height.h"
#include "Dvector.h"
#include "GerstnerWaveModel.h"
#include "PhilipsWaveModel.h"

//#define Version_Gerstner
#define Version_Philips

/** Point d'entree du programme, lance la simulation
*/
int main(int argc, char** argv) {
  /* Initialiser des paramètres de simulation */

  Dvector<double> windDirection(2, 2.0);
  double meanAlignment = 5.0;
  double intensity = 4.0;
  double meanWaveLength = 3.0;
  double heightAjustment = 2.0;

  #ifdef Version_Gerstner
  int nx = 128;
  int ny = 128;
  int Lx = 256;
  int Ly = 256;
  int time = 0;

  Dvector<double> Heightmap(nx*ny, 0.0);
  Height H(nx, ny, Heightmap);

  GerstnerWaveModel ModelGestnerWave;
  Ocean Surface(Lx, Ly, nx, ny, time, &H, (WaveModel*) &ModelGestnerWave);
  ocean = &Surface;

  double ampli1 = 10.0;
  double phi1 = 0.0;
  Dvector<double> dir1(2, 0.008);
  double freq1 = sqrt(9.81*dir1.norm());

  GerstnerWave G1 = GerstnerWave(ampli1, phi1, dir1, freq1);
  ModelGestnerWave.addWave(G1);

  double ampli2 = 15.0;
  double phi2 = 2.0;
  Dvector<double> dir2(2, 0.007);
  double freq2 = sqrt(9.81*dir2.norm());

  GerstnerWave G2 = GerstnerWave(ampli2, phi2, dir2, freq2);
  ModelGestnerWave.addWave(G2);
  #endif

  #ifdef Version_Philips
  int nx = 64;
  int ny = 64;
  int Lx = 128;
  int Ly = 128;
  int time = 0;

  Dvector<double> Heightmap(nx*ny, 0.0);
  Height H(nx, ny, Heightmap);

  double ampli = 15.0;
  Dvector<double> dir(2, 0.007);
  double freq = sqrt(9.81*dir.norm());
  PhilipsWave vaguePhilips(ampli, dir, freq);
  Dvector<double> wind(2, 7);

  PhilipsWaveModel ModelPhilipsWave(Lx, Ly, nx, ny, vaguePhilips, wind);

  Ocean Surface(Lx, Ly, nx, ny, time, &H, (WaveModel*) &ModelPhilipsWave);
  ocean = &Surface;
  //ocean->compute();
  #endif

  /* Initialisation de la fenêtre d'affichage */
  Window::init(WIDTH, HEIGHT, "Houle", argc, argv, "azerty", 50, 1);

  /* Execute la simulation */
  Window::launch();

  /* Libère la mémoire */
  Window::quit();
  delete ocean;

  return 0;

}
