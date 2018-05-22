#ifndef DVECTOR_H
#define DVECTOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <math.h>
#include <complex>

template <typename T>

class Dvector
{
    public:
    /** Dimension du vecteur
    */
    int dim;
    /** Valeur de toutes les composantes du vecteur
    */
    T* val;
    Dvector<T>();
    Dvector<T>(const Dvector<T> & V);
    Dvector<T>(int d, T v);
    ~Dvector<T>();
    Dvector<T>(std::string);
    void display(std::ostream& str);
    int size() const;
    void fillRandomly();
    T & operator() (int i) const;
    Dvector<T> & operator-();
    bool operator==(const Dvector<T> &);
    void operator= (const Dvector<T> &);
    Dvector<T> & operator+= (const Dvector<T> &);
    Dvector<T> & operator-= (const Dvector<T> &);
    Dvector<T> & operator*= (const double &);
    Dvector<T> & operator/= (const double &);
    double norm();
    void resize(const int, const T v);
    Dvector<T> conjugue() const;
};

template <typename T>
std::ostream & operator<<(std::ostream &, const Dvector<T> &);
template <typename T>
std::istream & operator>>(std::istream &, const Dvector<T> &);
template <typename T>
Dvector<T> operator+ (const Dvector<T> &, const Dvector<T> &);
template <typename T>
Dvector<T> operator- (const Dvector<T> &, const Dvector<T> &);
template <typename T>
T operator* (const Dvector<T> &, const Dvector<T> &);
template <typename T>
Dvector<T> operator* (const Dvector<T> &, const double &);
template <typename T>
Dvector<T> operator* (const double &, const Dvector<T> &);
template <typename T>
Dvector<T> operator/ (const Dvector<T> &, const double &);

#endif
