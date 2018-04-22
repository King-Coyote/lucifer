#include <iostream>
#include <fstream>
#include "ObjectFactoryJson.h"
#include "RenderObject.h"
#include "RenderObjectSphere.h"
#include "RenderObjectPlane.h"
#include "RenderObjectPointLight.h"
#include "RenderMaterial.h"

using namespace std;

ObjectFactoryJson::ObjectFactoryJson(const string& filename) {
    ifstream ifs(filename);
    ifs >> this->obj;
    ifs.close();
}

ObjectFactoryJson::~ObjectFactoryJson() {}

vector<unique_ptr<RenderObject>> ObjectFactoryJson::createObjects() const {

    Json::Value objects = this->obj["objects"];
    vector<unique_ptr<RenderObject>> sceneObjects = vector<unique_ptr<RenderObject>>();
    if (objects.isNull() || objects.empty()) {
        return sceneObjects; // empty vector if u done fuck up
    }

    for (int i = 0; i<objects.size(); ++i) {
        if (!objects[i].isObject()) {
            continue;
        }
        try {
            string type = objects[i]["type"].asString();
            RenderMaterial material = this->getMaterialFromJson(objects[i]["material"].asString());
            Vec position = this->getVecFromJson(objects[i]["position"]);
            if (type == "sphere") {
                sceneObjects.push_back(unique_ptr<RenderObject>(new RenderObjectSphere(
                    position,
                    objects[i]["id"].asString(),
                    objects[i]["radius"].asFloat(),
                    material
                )));
            } else if (type == "plane") {
                sceneObjects.push_back(unique_ptr<RenderObject>(new RenderObjectPlane(
                    position,
                    objects[i]["id"].asString(),
                    this->getVecFromJson(objects[i]["normal"]),
                    material
                )));
            } else if (type == "mesh") {
                continue; // TODO maybe make this kind of object dumbass
            } else {
                continue;
            }
        } catch (const exception& e) {
            cerr << "Object not created: "  << e.what() << endl;
            continue;
        }
    }
    return sceneObjects;
}

unique_ptr<RenderObject> ObjectFactoryJson::createObject() const {
    // not really valid for this boi
}

vector<unique_ptr<RenderObject>> ObjectFactoryJson::createLights() const {
    Json::Value lights = this->obj["lights"];
    vector<unique_ptr<RenderObject>> sceneLights = vector<unique_ptr<RenderObject>>();
    if (lights.isNull() || lights.empty()) {
        return sceneLights; // empty vector if u done fuck up
    }

    for (int i = 0; i<lights.size(); ++i) {
        if (!lights[i].isObject()) {
            continue;
        }
        try {
            Vec position = getVecFromJson(lights[i]["position"]);
            Pixel color = getColorFromJson("white");
            RenderMaterial material = RenderMaterial(lights[i]["emittance"].asFloat(), color);
            sceneLights.push_back(unique_ptr<RenderObject>(new RenderObjectPointLight(
                position,
                lights[i]["id"].asString(),
                color,
                lights[i]["emittance"].asFloat()
            )));
        } catch (const exception& e) {
            cerr << "Object not created: " << e.what() << endl;
            continue;
        }
    }
    return sceneLights;
}

unique_ptr<RenderObject> ObjectFactoryJson::createLight() const {
    // also not really relevant for this boi
}


Pixel ObjectFactoryJson::getColorFromJson(const string& handle) const {
    Json::Value colorJson = this->obj["colors"][handle];
    return Pixel(
        colorJson["r"].asFloat(),
        colorJson["g"].asFloat(),
        colorJson["b"].asFloat()
    );
}

RenderMaterial ObjectFactoryJson::getMaterialFromJson(const string& handle) const {
    Json::Value materialJson = this->obj["materials"][handle];
    return RenderMaterial(
        materialJson["emittance"].asFloat(),
        materialJson["transparent"].asBool(),
        materialJson["refrIndex"].asFloat(),
        materialJson["specularity"].asFloat(),
        this->getColorFromJson(materialJson["color"].asString())
    );
}

Vec ObjectFactoryJson::getVecFromJson(const Json::Value& jsonObj) const {
    return Vec(
        jsonObj["x"].asFloat(),
        jsonObj["y"].asFloat(),
        jsonObj["z"].asFloat()
    );
}