#pragma once

#include <string>
#include "RenderObject.h"
#include "RenderRay.h"
#include "RenderVec.h"

class RenderObjectPlane : public RenderObject {
public:
    RenderObjectPlane(Vec centerPosition, Vec n, string id, RenderMaterial material);
    ~RenderObjectPlane() {}

    Hit getIntersection(const Ray& ray) const;
    Vec getNormalAtPoint(const Vec& point) const;
private:
    Vec normal;
    // the number d relates the plane's position to its normal. It's used in intersection, so I define it at
    // construction to save calculation time.
    float d; 
};