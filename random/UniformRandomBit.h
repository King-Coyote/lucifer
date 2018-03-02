#pragma once

#include "UniformRandom.h"

class UniformRandomBit : public UniformRandom {
public: // METHODS
    UniformRandomBit();

    virtual float  getUniformRandom();
    virtual void    setSeed(unsigned int seed);
private: // MEMBERS
    unsigned int    currentVal;
    bool            seedSet;
};