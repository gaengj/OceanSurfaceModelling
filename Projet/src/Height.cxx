/**
 * \file Height.cxx
 * \brief Classe contenant l'ensemble des hauteurs calculées
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */
#include "Height.h"
#include <assert.h>

Height::Height()
{
    nx = 0;
    ny = 0;
    val = Dvector<double>();
}

/** Constructeur d'initialisation
 * @param[in] x nombre de points de discrétisation selon x
 * @param[in] y nombre de points de discrétisation selon y
 * @param[in] values Dvecteur contenant la valeur des hauteurs
 */
Height::Height(int x, int y, Dvector<double> values)
{
    /* On s'assure a la creation de la Heightmap qu'on ne donne pas un vecteur trop
     grand */
    assert(values.dim <= x*y);

    nx = x;
    ny = y;
    val = values;

    /* Si dim du vecteur plus petit que la taille de la Heightmap, on remplit les
    coeffs restants avec des 0*/
    if(values.dim < x*y){
        val.resize(nx*ny, 0.0);
    }

}

/** Constructeur par recopie
*/
Height::Height(const Height & H)
{
    nx = H.size_x();
    ny = H.size_y();
    val = Dvector<double>(H.values());
}

/** Constructeur par recopie
*/
void Height::operator= (const Height & H)
{
    nx = H.size_x();
    ny = H.size_y();
    val = Dvector<double>(H.values());
}

/** Operateur d'égalité
*/
bool Height::operator==(const Height & V)
{
    return ( (nx == V.size_x()) && (ny == V.size_y()) && (val == V.values()) );
}

/** Destructeur
*/
Height::~Height()
{

}

/** Accesseur du nombre de points de discrétisation selon x
*/
int Height::size_x() const
{
    return nx;
}

/** Accesseur du nombre de points de discrétisation selon y
*/
int Height::size_y() const
{
    return ny;
}

/** Accesseur des valeurs
*/
Dvector<double> Height::values() const
{
    return val;
}

/** Operateur d'accession
*/
double & Height::operator() (int x, int y) const
{
    if(0 <= x && x < size_x() && 0<=y && y<size_y()){
        return val(x*ny+y);
    }
    exit(-1);
}

// int main(){
//   return 0;
// }
