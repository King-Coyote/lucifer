
#include <random>

using namespace std;

class UniformRandom {
public: // METHODS 
    virtual float  getUniformRandom() = 0;
    virtual void    setSeed(unsigned int seed) = 0;
public: // MEMBERS
private:

};