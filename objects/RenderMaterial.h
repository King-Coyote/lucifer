#pragma once

#include <string>
#include "RenderPixel.h"

class Ray;
class Vec;
class UniformRandom;

enum class RenderMaterialType {
    DIFFUSE,
    SPECULAR,
    GLOSSY,
    REFRACTIVE
};

class RenderMaterial {
public: // METHODS
    RenderMaterial();
    RenderMaterial(RenderMaterialType type, Pixel color);
    RenderMaterial(float emittance, Pixel color); // for making lights
    RenderMaterial(float emittance, float transparency, float refrIndex, float specularity, float diffusion, Pixel color);
    RenderMaterial(std::string filename); //construct from JSON?

    // these return their coefficients to handle proportion of transmission/reflection
    void   transmuteTransmittedRay (Ray& ray, const Vec& hitNormal, UniformRandom& random) const;
    void   transmuteReflectedRay   (Ray& ray, const Vec& hitNormal, UniformRandom& random) const;
    float  getReflectionCoefficient(const Ray& ray, const Vec& surfaceNormal) const;
    float  getReflectionCost       (const Ray& ray, const Vec& normal) const;
    float  getTransmissionCost     (const Ray& ray, const Vec& normal) const;

    // getters
    Pixel  getColor() const;
    float  getEmittance() const;
private: //MEMBERS
    float emittance;
    float transparency;
    float refrIndex;
    float specularity; // this is related to diffusion by 1-specularity
    float diffusion;
    float transmissionCoefficient;
    Pixel color;
};