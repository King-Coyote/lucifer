#include <math.h>
#include "RenderSampler.h"
#include "RenderVec.h"

using namespace std;

RenderSampler::RenderSampler() :
    haltonBases({2, 3}),
    haltonIndices({0, 0})
{
    invertedBases[0] = 1.0 / haltonBases[0];
    invertedBases[1] = 1.0 / haltonBases[1];
}

RenderSampler::RenderSampler(int baseOne, int baseTwo) {
    // make this when you need it.
}

Vec RenderSampler::simpleHemisphereSample(float u, float v) {
	// uniform random ray pointing out of a hemisphere
	// u and v need to be random numbers between 0 and 1 inclusive
	const float r = sqrt(1.0 - u*u);
	const float phi = 2 * 3.1415926 * v; // PI as magic number
	return Vec(cos(phi)*r, sin(phi)*r, u);
}

Vec RenderSampler::haltonHemisphereSample() {
	return this->simpleHemisphereSample(this->nextHalton(0), this->nextHalton(1));
}

float RenderSampler::nextHalton(int index) {
    float f = 1, val = 0;
	int i = this->haltonIndices[index]++;
	int count = 0;
	while (i > 0) {
		count++;
		f *= invertedBases[index];
		val += f * (i % haltonBases[index]);
		i = floor(i*invertedBases[index]);
	}
	return val;
}