#include "RenderObjectPointLight.h"
#include "RenderMaterial.h"
#include "RenderHit.h"

using namespace std;

RenderObjectPointLight::RenderObjectPointLight(Vec position, string id, Pixel color, float emittance) :
    RenderObject(position, id, RenderMaterial(emittance, color))
{}

Hit RenderObjectPointLight::getIntersection(const Ray& ray) const {
    return Hit(); // TODO do I need some kind of special light intersection that returns just the positoon of this light?
}

Vec RenderObjectPointLight::getNormalAtPoint(const Vec& point) const {
    return point - this->position;
}

Pixel RenderObjectPointLight::getExplicitLightContribution(const Ray& ray, const Hit& hit) const {
    Vec w = this->position - hit.hitPoint;
    return this->material.getColor() * this->material.getEmittance() * hit.hitNormal.dot(w); // TODO is this correct
}