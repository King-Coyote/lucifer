#include "RenderHit.h"

Hit::Hit() :
    t(0),
    hitObject(nullptr)
{}

Hit::Hit(float t, Vec hitPoint, Vec hitNormal, const RenderObject * hitObject) :
    t(t),
    hitPoint(hitPoint),
    hitNormal(hitNormal),
    hitObject(hitObject)
{}

Hit::operator bool() { 
    return (this->hitObject != nullptr); 
}