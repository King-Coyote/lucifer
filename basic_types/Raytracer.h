#pragma once

class UniformRandom;
class Pixel;
class Ray;
class Vec;
class RenderScene;

class Raytracer {
public:

    void tracePixel(Pixel& radiance, Ray& mainRay, const RenderScene& scene, UniformRandom& rand, unsigned int depth = 0);
private:
};