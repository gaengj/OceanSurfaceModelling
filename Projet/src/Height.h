#ifndef HEIGHT_H
#define HEIGHT_H

#include <cstdlib>
#include "Dvector.h"

class Height
{
    private:
    /** Nombre de points de discrétisation selon x
    */
    int nx;
    /** Nombre de points de discrétisation selon y
    */
    int ny;
    /** Dvecteur contenant l'ensemble des valeurs des hauteurs
    */
    Dvector<double> val;

    public:
    Height();
    Height(int x, int y, Dvector<double> values);
    Height(const Height & H);
    void operator= (const Height & H);
    bool operator==(const Height & V);
    ~Height();
    Dvector<double> values() const;
    double & operator() (int x, int y) const;
    int size_x() const;
    int size_y() const;
};

#endif
