#include <memory>
#include <omp.h>
#include <cstring>
#include "Raytracer.h"
#include "RenderObject.h"
#include "RenderHit.h"
#include "UniformRandom.h"
#include "RenderPixel.h"
#include "RenderScene.h"
#include "RenderRay.h"

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

    Pixel explicitLight;
    for (auto light : scene.getLights()) {
        // TODO: need to raytrace here to get collisions
        Ray toLight = Ray(intersect.hitPoint, (light->getPosition() - intersect.hitPoint));
        float lightDist = intersect.hitPoint.distanceTo(light->getPosition());
        Hit lightIntersect = scene.getClosestIntersect(toLight);
        if (lightDist < lightIntersect.t) {
            // light has nothing in the way, contribute light explicitly here
            explicitLight = explicitLight + light->getExplicitLightContribution(toLight, intersect);
        }
    }

    // TODO does the radiance need to be divided by the PDF at the hit point?
    Pixel li; // Li from the integration of all incident light sources equation
    this->tracePixel(li, mainRay, scene, rand, depth + 1);
    radiance = radiance + li*material.getColor() * transmuteCost;
    radiance += explicitLight*material.getColor();
}