#include <ctime>
#include "UniformRandomBit.h"

using namespace std;

UniformRandomBit::UniformRandomBit() :
    currentVal(0),
    seedSet(false)
{}

float UniformRandomBit::getUniformRandom() {

    if (!seedSet) {
        seedSet = true;
        this->currentVal = (unsigned int)time(NULL);
    }

    unsigned int x = this->currentVal;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    this->currentVal = x;
    return x/(float)UINT32_MAX;
}

void UniformRandomBit::setSeed(unsigned int seed) {
    this->currentVal = seed;
}