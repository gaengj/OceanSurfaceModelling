/** 
 * \file Dvector.cxx
 * \brief Classe Vecteur générique pour les <double> et les <std::complex<double>>
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "Dvector.h"
#include <iostream>
#include <complex>
#include <cassert>

/** Constructeur par défaut, initialise la dimension du vecteur a 0
 */
template <typename T>
Dvector<T>::Dvector()
{
    dim = 0;
    val = new T[dim];
}

/** Constructeur par recopie
 */
template <typename T>
Dvector<T>::Dvector(const Dvector<T> & V)
{
    dim = V.dim;
    if(dim == 0) return;
    val = new T[dim];
    for(int i = 0; i<dim; i++) {
        val[i] = V.val[i];
    }
}

/** Constructeur d'initialisation
 * @param[in] d dimension du vecteur
 * @param[in] v valeur de chaque composante du vecteur
 */
template <typename T>
Dvector<T>::Dvector(int d, T v)
{
    dim = d;
    if (dim == 0) {
        return;
    }
    try {
      val = new T[dim];
    } catch(...) {
      printf("Could not allocate vector\n");
    }
    for(int i=0; i<dim; i++) {
        val[i] = v;
    }
}

// Dvector<T>::Dvector(std::string filename)
// {
//     std::ifstream file(filename);
//     std::string line;
//     if(file.is_open()) {
//         int number_of_lines = 0;
//         std::ifstream myfile(filename);
//         while (std::getline(myfile, line))
//             ++number_of_lines;
//         dim = number_of_lines;
//         val = new double[dim];
//         std::string token;
//         int i=0;
//         while(getline(file, line))
//         {
//             val[i] = std::stoi(line);
//             i++;
//         }
//     }
//     else {
//       printf("Error opening file\n");
//     dim = 0;
//     val = new double[dim];
// }
// }

/** Destructeur
 */
template <typename T>
Dvector<T>::~Dvector()
{
    delete [] val;
}

/** Affiche les valeurs contenues dans le vecteur
 */
template <typename T>
void Dvector<T>::display(std::ostream& str)
{
    for(int i=0; i< this->dim; i++) {
        str<<val[i]<<"\n";
    }
}

/** Renvoie la taille du vecteur (i.e sa dimension)
 */
template <typename T>
int Dvector<T>::size() const
{
    return dim;
}

// void Dvector<T>::fillRandomly()
// {
//     std::default_random_engine generator;
//     std::uniform_real_distribution<double> distribution(0.0,1.0);
//     for(int i=0; i< this->dim; i++) {
//         val[i] = distribution(generator);
//     }
// }

/** Operateur d'accession, renvoie la valeur de la composante du vecteur 
 * d'indice i passe en parametre
 */
template <typename T>
T & Dvector<T>::operator() (int i) const
{
    if(0 <= i && i < size()){
        return val[i];
    }
    exit(-1);
}

/** Operateur moins unaire
 */
template <typename T>
Dvector<T> & Dvector<T>::operator-()
{
    Dvector<T> &W = *this;
    for(int i = 0; i < dim; i++){
        W(i) = -W(i);
    }
    return W;
}

/** Operateur d'egalite
 */
template <typename T>
bool Dvector<T>::operator==(const Dvector<T> & V)
{
    Dvector<T> &W = *this;
    for(int i = 0; i<dim; i++) {
        if(W.val[i] != V.val[i])
        {return false;}
    }
    return true;
}

/** Operateur d'affectation
 */
template <typename T>
void Dvector<T>::operator= (const Dvector<T> & V)
{
    dim = V.dim;
    val = new T[dim];
    for(int i = 0; i<dim; i++) {
        val[i] = V.val[i];
    }
}

/** Operateur plus egal (addition de deux vecteurs)
 */
template <typename T>
Dvector<T> & Dvector<T>::operator+= (const Dvector<T> & V)
{
    if (dim != V.dim) {
        exit(-1);
    }
    Dvector<T> &W = *this;
    for(int i = 0; i < dim; i++){
        W(i)+=V(i);
    }
    return W;
}

/** Operateur moin egal (soustraction de deux vecteurs)
 */
template <typename T>
Dvector<T> & Dvector<T>::operator-= (const Dvector<T> & V)
{
    if (dim != V.dim) {
        exit(-1);
    }
    Dvector<T> &W = *this;
    for(int i = 0; i < dim; i++){
        W(i)-=V(i);
    }
    return W;
}

/** Operateur fois egal (multiplication d'un vecteur par un scalaire)
 */
template <typename T>
Dvector<T> & Dvector<T>::operator*= (const double & d)
{
    Dvector<T> &W = *this;
    for(int i = 0; i < dim; i++){
        W(i)*=d;
    }
    return W;
}

/** Operateur de division d'un vecteur par un scalaire
 */
template <typename T>
Dvector<T> & Dvector<T>::operator/= (const double & d)
{
    Dvector<T> &W = *this;
    for(int i = 0; i < dim; i++){
        W(i)/=d;
    }
    return W;
}

/** Permet de redimensionner le vecteur 
 * @param[in] taille nouvelle taille du vecteur
 * @param[in] nouvelles_valeurs la valeur des composantes ajoutees
 * dans le cas ou la nouvelle taille est plus grande que la taille
 * d'origine
 */
template <typename T>
void Dvector<T>::resize(const int taille, const T nouvelles_valeurs)
{
    if(size()<taille){
        int dim_tmp = this->dim;
        T *val_tmp = this->val;
        this->dim = taille;
        this->val = new T[taille];
        Dvector<T> &W = *this;
        for(int i = 0; i < dim_tmp; i++){
            W(i)=val_tmp[i];
        }
        for(int i = dim_tmp; i < taille; i++){
            W(i)=nouvelles_valeurs;
        }
    } else {
        this->dim = taille;
    }
}

/** Operateur d'addition entre deux vecteurs
 */
template <typename T>
Dvector<T> operator+(const Dvector<T> & V, const Dvector<T> & W)
{
    Dvector<T> X(V);
    X += W;
    return X;
}

/** Operateur de soustraction entre deux vecteurs
 */
template <typename T>
Dvector<T> operator-(const Dvector<T> & V, const Dvector<T> & W)
{
    Dvector<T> X(V);
    X -= W;
    return X;
}

/** Operateur de produit scalaire entre deux vecteurs
 */
template <typename T>
T operator*(const Dvector<T> & V, const Dvector<T> & W)
{   
    assert(V.size() == W.size());
    T X = V(0)*W(0);
    for(int i = 1; i<V.size(); i++){
        X += V(i)*W(i);
    }
    return X;
}

/** Operateur du produit d'un vecteur par un scalaire
 */
template <typename T>
Dvector<T> operator*(const Dvector<T> & V, const double & d)
{
    Dvector<T> X(V);
    X *= d;
    return X;
}

/** Operateur du produit d'un scalaire par un vecteur
 */
template <typename T>
Dvector<T> operator*(const double & d, const Dvector<T> & V)
{
    return V*d;
}

/** Operateur division d'un vecteur par un scalaire
 */
template <typename T>
Dvector<T> operator/(const Dvector<T> & V, const double & d)
{
    Dvector<T> X(V);
    X /= d;
    return X;
}

/** Operateur <<
 */
template <typename T>
std::ostream & operator<<(std::ostream & Out, const Dvector<T> & V)
{
    Out<<"Point: ";
    for(int i=0; i<V.dim; i++)
    { Out << V(i) << " ";}
    Out << std::endl;
    return Out;
}

/** Operateur >>
 */
template <typename T>
std::istream & operator>>(std::istream &in, const Dvector<T> &V)
{
    for(int i=0; i<V.dim; i++)
    {in >> V(i);}
    return in;
}

/** Renvoie la norme du vecteur pour un Dvector<double>
 */
template <>
double Dvector<double>::norm()
{
    double norm = 0;
    for(int i = 0; i<dim; i++) {
        norm += val[i]*val[i];
    }
    return sqrt(norm);
}

/** Renvoie la norme du vecteur pour un Dvector<std::complex<double>>
 */
template <>
double Dvector<std::complex<double>>::norm()
{
   
    return sqrt(std::real((*this)*this->conjugue()));
}

/** Renvoie le vecteur des conjugues
 */
template <typename T>
Dvector<T> Dvector<T>::conjugue() const
{
    Dvector<T> W(*this);
    for(int i = 0; i<dim; i++) {
        W(i)=std::conj(W(i));
    }
    return W;
}

template class Dvector<std::complex<double>>;
template class Dvector<double>;

