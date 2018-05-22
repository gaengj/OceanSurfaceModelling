/**
 * \file WaveModel.cxx
 * \brief Classe abstraite caractérisant une onde de manière générale
 * \author Naoto Lucas, Jean-Baptiste Gaeng
 */

#include "WaveModel.h"

/** Constructeur par défaut
*/
WaveModel::WaveModel()
{
    Dvector<double> A(2, 0.0);
    windDirection = A;
    meanAlignment = intensity = meanWaveLength = heightAjustment = 0;
}

/** Constructeur par recopie
*/
WaveModel::WaveModel(const WaveModel & V)
{
    windDirection = V.windDirection;
    meanAlignment = V.meanAlignment;
    intensity = V.intensity;
    meanWaveLength = V.meanWaveLength;
    heightAjustment = V.heightAjustment;
}

/** Destructeur
*/
WaveModel::~WaveModel()
{

}

/** Operateur d'affectation
*/
void WaveModel::operator= (const WaveModel &V)
{
    windDirection = V.windDirection;
    meanAlignment = V.meanAlignment;
    intensity = V.intensity;
    meanWaveLength = V.meanWaveLength;
    heightAjustment = V.heightAjustment;
}

/** Accesseur pour la direction du vent
*/
Dvector<double> WaveModel::getWindDirection() const
{
    return windDirection;
}

/** Accesseur pour l'alignement moyen
*/
double WaveModel::getMeanAlignment() const
{
    return meanAlignment;
}

/** Accesseur pour l'intensité
*/
double WaveModel::getIntensity() const
{
    return intensity;
}

/** Accesseur pour la longueur d'onde moyenne
*/
double WaveModel::getMeanWaveLength() const
{
    return meanWaveLength;
}

/** Accesseur pour l'ajustement de la hauteur
*/
double WaveModel::getHeightAjustment() const
{
    return heightAjustment;
}
