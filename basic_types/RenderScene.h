#pragma once

#include <vector>
#include <memory>

class Ray;
class RenderObject;
struct Hit;

using namespace std;

class RenderScene {
public: // METHODS

    Hit getClosestIntersect(const Ray &ray) const;
    void addObject(const RenderObject* obj);
    void addLight(const RenderObject* light);
    const vector<const RenderObject*>& getLights() const;
private: // MEMBERS
    vector<const RenderObject*> objects;
    vector<const RenderObject*> lights;
};