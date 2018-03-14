#include "RenderObjectPlane.h"
#include "RenderHit.h"

using namespace std;

RenderObjectPlane::RenderObjectPlane(Vec centerPosition, Vec n, string id, RenderMaterial material) :
    RenderObject(centerPosition, id, material),
    normal(n)
{
    this->d = n.dot(centerPosition);
}

Hit RenderObjectPlane::getIntersection(const Ray& ray) const {

    float nRo = this->normal.dot(ray.o); // dot product of plane normal and ray origin
    float nRd = this->normal.dot(ray.d);

    if (nRd == 0) {
        return Hit(); // this means tha t the ray is parallel to the normal, i.e. no intersections and a division by zero
    } else {
        float t = (this->d - nRo) / nRd;
        if (t > 1e-6) { // correct for self intersection
            return Hit(t, (ray.o + ray.d*t), this->normal, this);
        } else {
            return Hit(); // aint't a valid hit
        }
    }

}

Vec RenderObjectPlane::getNormalAtPoint(const Vec& point) const {
    return this->normal;
}