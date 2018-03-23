#pragma once

#include "UniformRandom.h"

class UniformRandomBit : public UniformRandom {
public: // METHODS
    UniformRandomBit();

    virtual float   getUniformRandom();
    // returns an int instead of the usual float.
    float           getUniformRandomInt();
    virtual void    setSeed(unsigned int seed);
    int             getCurrentVal() {return this->currentVal;}
private: // MEMBERS
    unsigned int    currentVal;
    bool            seedSet;
};