#include "RenderHit.h"

Hit::Hit() :
    t(0),
    hitObject(nullptr)
{}

Hit::Hit(float t, Vec hitPoint, Vec hitNormal, RenderObject * hitObject) :
    t(t),
    hitPoint(hitPoint),
    hitObject(hitObject)
{}

Hit::operator bool() { 
    return (this->hitObject != nullptr); 
}