#include <cmath>
#include <cstdio>
#include <memory>
#include "RenderScene.h"
#include "RenderHit.h"
#include "RenderRay.h"
#include "RenderObject.h"

using namespace std;

Hit RenderScene::getClosestIntersect(const Ray &ray) const {
    
    float minDistance = INFINITY;
    Hit closestHit = Hit();
    for (auto objPtr : this->objects) {
        Hit intersect = objPtr->getIntersection(ray);
        if (!intersect) {
            continue;
        }
        if (intersect.t < minDistance) {
            minDistance = intersect.t;
            closestHit = intersect;
        }
    }

    return closestHit;

}

void RenderScene::addObject(const RenderObject* obj) {
    this->objects.push_back(shared_ptr<const RenderObject>(obj));
    // if it emits light, add it to lights too.
    if (abs(obj->getMaterial().getEmittance()) > 1e-2) {
        this->lights.push_back(shared_ptr<const RenderObject>(obj));
    }
}

void RenderScene::addLight(const RenderObject* light) {
    if (light->getMaterial().getEmittance() <= 1e-2) {
        printf("WARNING: object emittance %f, needs to be > 0.01. Not added to scene lights.\n", light->getMaterial().getEmittance());
        return;
    }
    this->lights.push_back(shared_ptr<const RenderObject>(light));
}

const obj_vector& RenderScene::getLights() const {
    return this->lights;
}