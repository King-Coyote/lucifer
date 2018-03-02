#include "UniformRandom.h"

class UniformRandomMers : public UniformRandom {
public:
    UniformRandomMers();

    float  getUniformRandom();
    void    setSeed(unsigned int seed);
private:
    mt19937                             mers;
    uniform_real_distribution<float>   uniformDist;
};