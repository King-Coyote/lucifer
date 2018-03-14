#pragma once

#include "RenderObject.h"

class Ray;

class RenderObjectSphere : public RenderObject {
public:
    RenderObjectSphere(Vec centerPosition, float radius, string id, RenderMaterial material);

    Hit getIntersection(const Ray& ray) const;
    Vec getNormalAtPoint(const Vec& point) const;
private:
    float radius;
};