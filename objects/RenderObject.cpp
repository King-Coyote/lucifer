#include "RenderObject.h"
#include "RenderHit.h"

RenderObject::RenderObject(Vec position, string id) :
    position(position),
    id(id)
{}

RenderObject::RenderObject(Vec position, string id, RenderMaterial material) :
    position(position),
    id(id),
    material(material)
{}


Pixel RenderObject::getExplicitLightContribution(const Ray& ray, const Hit& hitPoint) const {
    return Pixel(0.0f, 0.0f, 0.0f);
}

const RenderMaterial& RenderObject::getMaterial() const {
    return this->material;
}