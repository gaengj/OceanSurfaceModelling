/**
 * \file GerstnerWaveModel.cxx
 * \brief Classe permettant de stocker les instances des differentes vagues de
 * Gerstner créées
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "GerstnerWaveModel.h"

/** Constructeur par défaut, initialise la liste des ondes de Gerstner par une
 * liste vide
 */
GerstnerWaveModel::GerstnerWaveModel()
{
        std::list<GerstnerWave> GerstnerWaveList = {};
}

/** Constructeur par recopie
*/
GerstnerWaveModel::GerstnerWaveModel(const GerstnerWaveModel & G)
{
    std::list<GerstnerWave> GerstnerWaveList(G.GerstnerWaveList);
}

/** Operateur d'affectation
*/
void GerstnerWaveModel::operator= (const GerstnerWaveModel & G)
{
    std::list<GerstnerWave> GerstnerWaveList(G.GerstnerWaveList);
}

/** Permet d'ajouter une vague à la liste des ondes de Gerstner
*/
void GerstnerWaveModel::addWave(const GerstnerWave & G)
{
    GerstnerWaveList.push_front(G);
}

/** Destructeur
*/
GerstnerWaveModel::~GerstnerWaveModel()
{
    GerstnerWaveList.clear();
}

/** Operateur d'accession, renvoit la hauteur d'un point de coordonnées (x,y) à
* un temps t, correspondant à la somme des hauteurs en ce point pour chaque
* instance des ondes de Gersner créées
*/
double GerstnerWaveModel::operator() (int x, int y, int t)
{
    double somme = 0;
    for (std::list<GerstnerWave>::const_iterator it = GerstnerWaveList.begin(); it != GerstnerWaveList.end(); it++)
      somme += (*it)(x, y, t);
    return somme;
}
