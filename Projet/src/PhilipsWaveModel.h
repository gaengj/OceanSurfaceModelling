#include <list>
#include "PhilipsWave.h"
#include "WaveModel.h"
#include "Height.h"

class PhilipsWaveModel : public WaveModel
{
public:
    PhilipsWave vague;
    Height hauteur;
    int tempsSauvegarde = -1;
    int Lx;
    int Ly;
    public:
    PhilipsWaveModel(int lx, int ly, int nx, int ny, PhilipsWave &W, Dvector<double> & wind);
    PhilipsWaveModel(const PhilipsWaveModel & G);
    void operator= (const PhilipsWaveModel & G);
    ~PhilipsWaveModel();
    void compute(int t);
    double operator() (int x, int y, int t);
};
