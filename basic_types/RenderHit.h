#pragma once

#include "RenderVec.h"

class RenderObject;

struct Hit {
    // handles intersections between objects and the ray that hits them
    // these are fully immutable after construction
    Hit();
    Hit(float t, Vec hitPoint, Vec hitNormal, const RenderObject * hitObject);

    float          t; // length of ray ie distance away
    Vec             hitPoint;
    Vec             hitNormal;
    const RenderObject*   hitObject;

    operator bool();
};