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
    for (auto obj : this->objects) {
        Hit intersect = obj->getIntersection(ray);
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

// TODO do you really need two separate methods if you're dictating which vector they go in anyway?...
void RenderScene::addObject(const RenderObject* obj) {
    this->objects.push_back(shared_ptr<const RenderObject>(obj));
}

void RenderScene::addLight(const RenderObject* light) {
    this->lights.push_back(shared_ptr<const RenderObject>(light));
}

const obj_vector& RenderScene::getLights() const {
    return this->lights;
}