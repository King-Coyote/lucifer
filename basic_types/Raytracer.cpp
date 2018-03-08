#include <memory>
#include "Raytracer.h"
#include "RenderObject.h"
#include "RenderHit.h"
#include "UniformRandom.h"
#include "RenderPixel.h"
#include "RenderScene.h"

using namespace std;

void Raytracer::tracePixel(Pixel& radiance, Ray& mainRay, const RenderScene& scene, UniformRandom& rand, unsigned int depth) {

    // TODO perhaps this should be replaced by a RR later on
    if (depth > 5) {
        return;
    }

    Hit intersect = scene.getClosestIntersect(mainRay);
    if (!intersect) {
        return;
    }

    const RenderMaterial& material = intersect.hitObject->getMaterial();

    // TODO make this reflection coefficient work properly - for now, just 1.0 for always diffuse.
    //float R = material.getReflectionCoefficient(mainRay, intersect.hitNormal);
    float R = 1.0f;
    float transmuteCost = 1.0f;

    if (rand.getUniformRandom() < R) {
        material.transmuteReflectedRay(mainRay, intersect.hitNormal, rand);
        transmuteCost = material.getReflectionCost(mainRay, intersect.hitNormal);
    } else {
        material.transmuteTransmittedRay(mainRay, intersect.hitNormal, rand);
        transmuteCost = material.getTransmissionCost(mainRay, intersect.hitNormal);
    }

    Pixel explicitLight; // TODO is this initialised using implicit constructor or to random floats? eek
    for (auto light : scene.getLights()) {
        explicitLight = light->getExplicitLightContribution(mainRay, intersect);
    }

    Pixel li; // Li from the integration of all incident light sources equation
    this->tracePixel(li, mainRay, scene, rand, depth + 1);
    radiance = radiance + li*material.getColor() * transmuteCost;
    radiance += explicitLight;
}