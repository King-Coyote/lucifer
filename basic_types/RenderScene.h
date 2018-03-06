#pragma once

#include <vector>
#include <memory>

class Ray;
class RenderObject;
struct Hit;

using namespace std;

typedef vector<shared_ptr<const RenderObject>> obj_vector;

class RenderScene {
public: // METHODS

    Hit getClosestIntersect(const Ray &ray) const;
    void addObject(const RenderObject* obj);
    void addLight(const RenderObject* light);
    const obj_vector& getLights() const;
private: // MEMBERS
    obj_vector objects;
    obj_vector lights;
};