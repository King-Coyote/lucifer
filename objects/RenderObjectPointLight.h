#pragma once

#include <string>
#include "RenderPixel.h"
#include "RenderObject.h"

class Vec;
struct Hit;

using namespace std;

class RenderObjectPointLight : public RenderObject {
public:
    RenderObjectPointLight(Vec position, string id, Pixel color, float emittance);

    virtual Hit getIntersection(const Ray& ray) const;
    virtual Vec getNormalAtPoint(const Vec& point) const;
    virtual Pixel getExplicitLightContribution(const Ray& ray, const Hit& hit) const;
private:

};