#pragma once

#include <memory>
#include <vector>

class RenderObject;

using namespace std;

class ObjectFactory {
public:
    ObjectFactory() {}
    virtual ~ObjectFactory() {}

    virtual vector<unique_ptr<RenderObject>> createObjects() const = 0;
    virtual unique_ptr<RenderObject> createObject() const = 0;

};