#include <list>
#include "GerstnerWave.h"
#include "WaveModel.h"

class GerstnerWaveModel : public WaveModel
{
    /** Liste contenant les differentes instances des ondes de Gerstner
    */
    std::list<GerstnerWave> GerstnerWaveList;
    public:
    GerstnerWaveModel();
    GerstnerWaveModel(const GerstnerWaveModel & G);
    void addWave(const GerstnerWave & G);
    void operator= (const GerstnerWaveModel & G);
    ~GerstnerWaveModel();
    double operator() (int x, int y, int t);
};
