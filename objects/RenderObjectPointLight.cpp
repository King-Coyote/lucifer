#include "RenderObjectPointLight.h"
#include "RenderMaterial.h"
#include "RenderHit.h"
#include "RenderVec.h"
#include "RenderRay.h"

using namespace std;

RenderObjectPointLight::RenderObjectPointLight(Vec position, string id, Pixel color, float emittance) :
    RenderObject(position, id, RenderMaterial(emittance, color))
{}

Hit RenderObjectPointLight::getIntersection(const Ray& ray) const {
    // TODO correctly return intersection for point light
    return Hit(this->position.distanceTo(ray.o), this->position, (ray.o - this->position).normalise(), this);
}

Vec RenderObjectPointLight::getNormalAtPoint(const Vec& point) const {
    return point - this->position;
}

Pixel RenderObjectPointLight::getExplicitLightContribution(const Ray& ray, const Hit& hit) const {
    Vec w = (this->position - hit.hitPoint).normalise();
    // TODO the dot product should be replaced by the material's BRDF once you have that going.
    return this->material.getColor() * this->material.getEmittance() * hit.hitNormal.dot(w);
}