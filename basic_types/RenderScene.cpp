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
    for (auto const& obj : this->objects) {
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

void RenderScene::setObjects(vector<unique_ptr<RenderObject>> objects) {
    this->objects = move(objects);
}

void RenderScene::setLights(vector<unique_ptr<RenderObject>> lights) {
    this->lights = move(lights);
}

// TODO do you really need two separate methods if you're dictating which vector they go in anyway?...
void RenderScene::addObject(RenderObject* obj) {
    this->objects.push_back(unique_ptr<RenderObject>(obj));
}

void RenderScene::addLight(RenderObject* light) {
    this->lights.push_back(unique_ptr<RenderObject>(light));
}

const obj_vector& RenderScene::getLights() const {
    return this->lights;
}