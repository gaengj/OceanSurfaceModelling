/**
 * \file Ocean.cxx
 * \brief Classe générale permettant de décrire l'évolution de la Houle
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "Ocean.h"

/** Constructeur d'initialisation
 * @param[in] long_x longueur de l'ocean en x
 * @param[in] long_y longueur de l'ocean en y
 * @param[in] nb_x nombre de points de discrétisation en x
 * @param[in] nb_y nombre de points de discrétisation en y
 * @param[in] time temps courant
 * @param[in] Height_map Ensemble des hauteurs de la surface
 * @param[in] Modele_Vague Modele considere parmi GerstnerWaveModel ou PhilipsWaveModel
 */
Ocean::Ocean(const int & long_x, const int & long_y, const int & nb_x, const int & nb_y, int & time, Height* Height_map, WaveModel* Modele_Vague)
{
  Lx = long_x;
  Ly = long_y;
  nx = nb_x;
  ny = nb_y;
  t = time;
  H = Height_map;

  Model = Modele_Vague;
}

/** Destructeur
*/
Ocean::~Ocean()
{
    //delete H et Model
}

/** Genere une surface initiale pour décrire la surface d'ocean
*/
Height Ocean::generateHeight()
{
      Dvector<double> Heightmap(nx*ny, 0.0);
      Height H0(nx, ny, Heightmap);
      return H0;
}

/** Permet de calculer les hauteurs de la surface d'Ocean
*/
Height Ocean::compute()
{
    /*Mettre a jour la Height_Map H en utilisant les fonctions compute
    (à implementer) du modele choisi : Gerstner ou Philips*/
    for(int y=0; y<ny; y++){
        for(int x=0; x<nx; x++){
            (*H)(x,y) = (*Model)((int)Lx*x/nx,(int)Ly*y/ny, t);
        }
    }
    return *H;
}

/** Incrémente le temps courant
*/
void Ocean::t_increment()
{
    t++;
}

/** Accesseur pour le nombre de points de discrétisation selon x
*/
int Ocean::getNx()
{
    return nx;
}

/** Accesseur pour le nombre de points de discrétisation selon y
*/
int Ocean::getNy()
{
    return ny;
}

/** Accesseur pour la longueur de la surface selon x
*/
int Ocean::getLx()
{
    return Lx;
}

/** Accesseur pour la longueur de la surface selon y
*/
int Ocean::getLy()
{
    return Ly;
}

/** Accesseur pour le temps courant
*/
int Ocean::getTime()
{
    return t;
}


/** Initialise la grille dans la direction x
 *  param[in]   y        abscisse de la colonne à parcourir
 *  param[out]  vertices buffer contenant les coordonnées des noeuds
 */

void Ocean::init_gl_VertexArrayX(const int y, double* const vertices) const {
  for(int x=0 ; x<nx ; x++) {
    vertices[3*x]   = (Lx/nx)*x;
    vertices[3*x+2] = (Ly/ny)*y;
  }
  vertices[3*nx]   = Lx;
  vertices[3*nx+2] = (Ly/ny)*y;
}

/** Initialise la grille dans la direction y
 *  param[in]   x        abscisse de la ligne à parcourir
 *  param[out]  vertices buffer contenant les coordonnées des noeuds
 */
void Ocean::init_gl_VertexArrayY(const int x, double* const vertices) const {
  for(int y=0 ; y<ny ; y++) {
    vertices[3*y]   = (Lx/nx)*x;
    vertices[3*y+2] = (Ly/ny)*y;
  }
  vertices[3*ny]   = (Lx/nx)*x;
  vertices[3*ny+2] = Ly;
}

/** Convertit le champs de hauteur en tabeau directement utilisable
 *  par OpenGL pour un y donné
 *  param[in]   y        abscisse de la colonne à parcourir
 *  param[out]  vertices buffer contenant les valeurs aux noeuds
 */
void Ocean::gl_VertexArrayX(const int y, double* const vertices) const {
  for(int x=0 ; x<nx ; x++) {
    vertices[3*x+1] = pow(-1, x+y)*(*H)(y,x);
  }
  vertices[3*nx+1] = pow(-1, nx+y)*(*H)(y,0);
}

/** Convertit le champs de hauteur en tabeau directement utilisable
 *  par OpenGL pour un x donné
 *  param[in]   x        abscisse de la ligne à parcourir
 *  param[out]  vertices buffer contenant les valeurs aux noeuds
 */
void Ocean::gl_VertexArrayY(const int x, double* const vertices) const {
  for(int y=0 ; y<ny ; y++) {
    vertices[3*y+1] = (*H)(y,x);
  }
  vertices[3*ny+1]  = (*H)(0,x);
}
