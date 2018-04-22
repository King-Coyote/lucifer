#pragma once

#include "RenderObject.h"

class Ray;

class RenderObjectSphere : public RenderObject {
public:
    RenderObjectSphere(Vec centerPosition, string id, float radius, RenderMaterial material);
    ~RenderObjectSphere() {}

    Hit getIntersection(const Ray& ray) const;
    Vec getNormalAtPoint(const Vec& point) const;
private:
    float radius;
};