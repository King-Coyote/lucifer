#pragma once

#include <vector>
#include <memory>

class Ray;
class RenderObject;
struct Hit;

using namespace std;

typedef vector<unique_ptr<RenderObject>> obj_vector;

class RenderScene {
public: // METHODS

    Hit getClosestIntersect(const Ray &ray) const;
    void setObjects(vector<unique_ptr<RenderObject>> objects);
    void setLights(vector<unique_ptr<RenderObject>> lights);
    void addObject(RenderObject* obj);
    void addLight(RenderObject* light);
    const obj_vector& getLights() const;
private: // MEMBERS
    obj_vector objects;
    obj_vector lights;
};