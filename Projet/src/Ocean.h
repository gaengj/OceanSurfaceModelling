#ifndef OCEAN_H
#define OCEAN_H

#include <cstdlib>
#include "Dvector.h"
#include "Height.h"
#include "WaveModel.h"
#include <vector>

class Ocean
{
    private:
    /** longueur de l'ocean en x
    */
    int Lx;
    /** longueur de l'ocean en y
    */
    int Ly;
    /** nombre de points de discrétisation en x
    */
    int nx;
    /** nombre de points de discrétisation en y
    */
    int ny;
    /** temps courant
    */
    int t;
    /** Pointeur sur la map des hauteurs
    */
    Height *H;
    /** Pointeur sur le modèle de vague considérée
    */
    WaveModel* Model;
    /** Interface les vecteurs de calculs avec le système de visualisation
    */
    std::vector<double> vertices;

    public:
    Ocean(const int & long_x, const int & long_y, const int & nb_x, const int & nb_y, int & time, Height* Height_map, WaveModel* Vague_Modele);
    ~Ocean();
    Height generateHeight();
    Height compute();
    void t_increment();
    void init_gl_VertexArrayX(const int y, double* const vertices) const;
    void init_gl_VertexArrayY(const int x, double* const vertices) const;
    void gl_VertexArrayX(const int y, double* const vertices) const;
    void gl_VertexArrayY(const int x, double* const vertices) const;
    int getNx();
    int getNy();
    int getLx();
    int getLy();
    int getTime();

};

#endif
