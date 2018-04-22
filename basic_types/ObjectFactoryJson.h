#pragma once

#include <json/json.h>
#include <memory>
#include <string>
#include "ObjectFactory.h"
#include "RenderPixel.h"
#include "RenderMaterial.h"
#include "RenderVec.h"

class RenderObjectSphere;
class RenderObjectPlane;

class RenderObject;

using namespace std;

class ObjectFactoryJson : public ObjectFactory {
public: // METHODS
    explicit ObjectFactoryJson(const string& filename);
    virtual ~ObjectFactoryJson();

    vector<unique_ptr<RenderObject>> createObjects() const override;
    vector<unique_ptr<RenderObject>> createLights() const override;
    unique_ptr<RenderObject> createObject() const override;
    unique_ptr<RenderObject> createLight() const override;

private: // MEMBERS
    Json::Value obj;

private: // METHODS
    RenderObjectSphere* getSphereFromJson();
    RenderObjectPlane* getPlaneFromJson();
    Pixel getColorFromJson(const string& handle) const;
    RenderMaterial getMaterialFromJson(const string& handle) const;
    Vec getVecFromJson(const Json::Value& jsonObj) const;

};