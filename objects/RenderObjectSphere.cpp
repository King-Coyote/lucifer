#include <cmath>
#include "RenderHit.h"
#include "RenderObjectSphere.h"
#include "RenderRay.h"

Hit RenderObjectSphere::getIntersection(const Ray& ray) const {
    // setup the B and C of the quadratic equation (At^2 + Bt + C = R^2, but A is 1 since the direction vector is normalised by construction)
    Vec diff = ray.o - this->position;
    float B = 2 * diff.dot(ray.d);
    float C = diff.dot(diff) - this->radius*this->radius;
    float dis = B*B - 4*C;
    if (dis < 0) {
        return Hit(); // if the discriminant is -ve, there is no real solution i.e. the ray has no intersections
    } else {
        // 2 cases for the two signs of the equation.
        float soln1 = (-B - sqrt(dis));
        float soln2 = (-B + sqrt(dis));
        if (soln1 > 1e-6) {
            Vec hitPoint = ray.o + ray.d*(soln1/2);
            return Hit(soln1 / 2, hitPoint, this->getNormalAtPoint(hitPoint), this);
        } else if (soln2 > 1e-6) {
            Vec hitPoint = ray.o + ray.d*(soln2/2);
            return Hit(soln2 / 2, hitPoint, this->getNormalAtPoint(hitPoint), this);
        } else {
            return Hit();
        }
    }
}

Vec RenderObjectSphere::getNormalAtPoint(const Vec& point) const {
    return (point - this->position).normalise();
}
