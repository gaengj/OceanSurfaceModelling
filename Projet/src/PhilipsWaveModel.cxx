#include "PhilipsWaveModel.h"
#include <cmath>
#include <complex>
#include "fft.h"

typedef std::complex<double> dcomp;

PhilipsWaveModel::PhilipsWaveModel(int lx, int ly, int nx, int ny, PhilipsWave &W,  Dvector<double> & wind)
{
    hauteur = Height(nx, ny, Dvector<double>(nx*ny,0));
    Lx = lx;
    Ly = ly;
    PhilipsWave vague(W);
    windDirection = Dvector<double>(wind);
}

PhilipsWaveModel::PhilipsWaveModel(const PhilipsWaveModel & G)
{
    Height hauteur(G.hauteur);
}
void PhilipsWaveModel::operator= (const PhilipsWaveModel & G)
{
    Height hauteur(G.hauteur);
}


PhilipsWaveModel::~PhilipsWaveModel()
{
}

double PhilipsWaveModel::operator() (int x, int y, int t)
{
    if (t!=tempsSauvegarde){
        compute(t);
    }
    return hauteur((int)(x*hauteur.size_x()/Lx), y*hauteur.size_y()/Ly);
}


void PhilipsWaveModel::compute(int t)
{
  tempsSauvegarde = t;
  int r = 0;
  for(int y = -hauteur.size_y()/2; y<hauteur.size_y()/2; y++){
      Dvector<dcomp> ligne(hauteur.size_x(),0);
      int i = 0;
      for(int x = -hauteur.size_x()/2; x<hauteur.size_x()/2-1; x++){
          double kx = 2*M_PI*x/Lx;
          double ky = 2*M_PI*y/Ly;
          Dvector<double> k(2,0);
          k(0) = kx;
          k(1) = ky;
          /* Calcul de P_h */
          double direction_carre = pow(kx, 2) + pow(ky, 2);
          double L = (pow(windDirection(0),2) + pow(windDirection(1),2))/9.81;
          double one_direction;
          one_direction = kx*windDirection(0)+ky*windDirection(1);
          double P_h = 5*(exp(-1/(pow(L,2)*direction_carre))/(direction_carre))*(pow((one_direction),2));

          /* Calcul de h_tilde */
          std::default_random_engine generator;
          std::normal_distribution<double> distribution(0.0,1.0);
          double xsi_r = distribution(generator);
          double xsi_i = distribution(generator);

          double omega_k = sqrt(9.81*sqrt(direction_carre));
          dcomp Xsi(xsi_r, xsi_i);
          dcomp theta(0.0, omega_k*t);
          dcomp comp1 = (Xsi)*exp(theta);
          dcomp h_tilde = sqrt(P_h/2)*(comp1 + std::conj(comp1));
          ligne(i) = h_tilde;
          i++;
      }
      Dvector<double> h = ifftDouble(ligne);
      for(int i=0; i<h.size(); i++){
          hauteur(i, r) = h(i);
      }
      r++;
  }
}
