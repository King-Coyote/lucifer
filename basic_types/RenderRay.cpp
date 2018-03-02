#include "RenderRay.h"

Ray::Ray(Vec o, Vec d) :
    o(o),
    d(d.normalise())
{}

string Ray::toString() {
    return "ray("
        + o.toString() + ","
        + d.toString()
        + ")";
}