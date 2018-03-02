#pragma once

class Vec;
class Ray;

class RenderSampler {
public:// METHODS
    RenderSampler();
    RenderSampler(int baseOne, int baseTwo);

    Vec simpleHemisphereSample(float u, float v);
    Vec haltonHemisphereSample();
private:// MEMBERS
    int haltonBases[2];
    float invertedBases[2];
    int haltonIndices[2];
private:// METHODS
    float nextHalton(int index);
};