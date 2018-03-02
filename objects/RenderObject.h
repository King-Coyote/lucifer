#pragma once

#include <string>
#include "RenderMaterial.h"
#include "RenderVec.h"

class RenderObject;
class Pixel;

struct Hit;
class Ray;

class RenderObject {
public:
    RenderObject(Vec position, string id);
    RenderObject(Vec position, string id, RenderMaterial material);

    const RenderMaterial& getMaterial() const;
    virtual Hit getIntersection(const Ray& ray) const = 0;
    virtual Vec getNormalAtPoint(const Vec& point) const = 0;
    virtual Pixel getExplicitLightContribution(const Ray& ray, const Hit& hitPoint) const;
protected:
    RenderMaterial material;
    Vec position;
    string id;
};