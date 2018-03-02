#include "UniformRandomMers.h"

using namespace std;

UniformRandomMers::UniformRandomMers() {
    random_device rd;
    this->mers = mt19937(rd());
}

float UniformRandomMers::getUniformRandom() {
    return this->uniformDist(this->mers);
}

void UniformRandomMers::setSeed(unsigned int seed) {
    this->mers = mt19937(seed);
}
