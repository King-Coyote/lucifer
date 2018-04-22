#include <math.h>
#include "RenderMaterial.h"
#include "UniformRandom.h"
#include "RenderVec.h"
#include "RenderRay.h"

RenderMaterial::RenderMaterial() :
    emittance(0),
    transparent(false),
    refrIndex(1),
    specularity(0),
    color(Pixel())
{}

RenderMaterial::RenderMaterial(RenderMaterialType type, Pixel color) {
    switch(type) {
    case RenderMaterialType::DIFFUSE:
        this->emittance = 0;
        this->transparent = false;
        this->refrIndex = 1;
        this->specularity = 0;
        break;
    case RenderMaterialType::GLOSSY:
        this->emittance = 0;
        this->transparent = false;
        this->refrIndex = 1;
        this->specularity = 50000.0f;
        break;
    case RenderMaterialType::REFRACTIVE:
        this->emittance = 0;
        this->transparent = true;
        this->refrIndex = 1.52;
        this->specularity = 0;
        break;
    case RenderMaterialType::SPECULAR:
        this->emittance = 0;
        this->transparent = false;
        this->refrIndex = 1;
        this->specularity = 0;
        break;
    }
    this->color = color;
}

RenderMaterial::RenderMaterial(float emittance, Pixel color) :
    emittance(emittance),
    transparent(false),
    refrIndex(1),
    specularity(0),
    color(color)
{}

RenderMaterial::RenderMaterial(float emittance, bool transparent, float refrIndex, float specularity, Pixel color) :
    emittance(emittance),
    transparent(transparent),
    refrIndex(refrIndex),
    specularity(specularity),
    color(color)
{}

RenderMaterial::RenderMaterial(std::string filename) {
 // don't do nothin right now
} 

void RenderMaterial::transmuteTransmittedRay(Ray& ray, const Vec& hitNormal, UniformRandom& random) const {
 
    //TODO I don't think you need the other getreflectioncoefficient thing - this will always give
    // reflection if the mateiral has refract index of 1
    float rN = 1 / this->refrIndex; // ref index of air assumed to be 1
    float cosI = (hitNormal * -1).dot(ray.d); // incident cosine lol
    float cosT = sqrt(1 - rN*rN*(1 - cosI*cosI)); // transmitted cosine
    float R0 = (1 - this->refrIndex) / (1 + this->refrIndex);
    R0 = R0*R0;
    if (cosI < 0) { 
        cosI = cosI * -1;
        rN = 1 / rN;
    }
    float R = R0 + (1 - R0)*pow(1 - cosI, 5.0); // this is the Schlick approximation, less expensive than doing the full calculation
    //if (cosT > 0 && R < random.getUniformRandom()) {
        ray.d = ray.d*rN + hitNormal*(rN*cosI - sqrt(1 - rN*rN*(1 - cosI*cosI)));
        ray.d.normalise();
    //} else {
        //ray.d = (ray.d + hitNormal*cosI*2).normalise();
    //}

}

void RenderMaterial::transmuteReflectedRay(Ray& ray, const Vec& hitNormal, UniformRandom& random) const {

    // intersection with glossy object, using phong cosine model
    float cos_i = (hitNormal * -1).dot(ray.d);
    Vec specDir = (ray.d + hitNormal*cos_i * 2).normalise();

	const float u_mod = pow(random.getUniformRandom(), 1 / (this->specularity + 1));
	const float r = sqrt(1.0 - u_mod*u_mod);
	const float phi = 2 * 3.1415926 * random.getUniformRandom();
    Vec sampleVec = Vec(cos(phi)*r, sin(phi)*r, u_mod);

    Vec orientedX, orientedY;
    specDir.formONS(orientedX, orientedY);
    Vec rotatedDir = Vec(
        Vec(orientedX.x, orientedY.x, specDir.x).dot(sampleVec),
        Vec(orientedX.y, orientedY.y, specDir.y).dot(sampleVec),
        Vec(orientedX.z, orientedY.z, specDir.z).dot(sampleVec)
    );
    // rotatedDir.x = Vec(orientedX.x, orientedY.x, specDir.x).dot(sampleVec);
    // rotatedDir.y = Vec(orientedX.y, orientedY.y, specDir.y).dot(sampleVec);
    // rotatedDir.z = Vec(orientedX.z, orientedY.z, specDir.z).dot(sampleVec);
    ray.d = rotatedDir.normalise();
    //float diffuseCost = ray.d.dot(hitNormal);
    //float specCost = pow(ray.d.dot(specDir), this->specularity);

}

float RenderMaterial::getReflectionCoefficient(const Ray& ray, const Vec& surfaceNormal) const {

    float R0 = (1 - this->refrIndex) / (1 + this->refrIndex);
    float rN = 1 / this->refrIndex; // ref index of air assumed to be 1
    float cosI = (surfaceNormal * -1).dot(ray.d); // incident cosine lol
    R0 = R0*R0;
    if (cosI < 0) {
        cosI = cosI * -1;
        rN = 1 / rN;
    }
    float R = R0 + (1 - R0)*pow(1 - cosI, 5.0);
    return R;

}

float RenderMaterial::getReflectionCost(const Ray& ray, const Vec& normal) const {
    return ray.d.dot(normal);
}

float RenderMaterial::getTransmissionCost(const Ray& ray, const Vec& normal) const {
    return 1.0; // should this be related to transmission coefficient? or used in SSS?
}

Pixel RenderMaterial::getColor() const {
    return this->color;
}

float RenderMaterial::getEmittance() const {
    return this->emittance;
}

bool RenderMaterial::getTransparent() const {
    return this->transparent;
}