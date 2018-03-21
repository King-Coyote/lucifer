#include "RenderVec.h"

#include <cmath>

using namespace std;

Vec::Vec() :
    x(0),
    y(0),
    z(0)
{}

Vec::Vec(float x, float y, float z) :
    x(x),
    y(y),
    z(z)
{}


Vec Vec::operator +(const Vec& v) const {
    return Vec(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vec Vec::operator -(const Vec& v) const {
        return Vec(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vec Vec::operator *(float c) const {
    return Vec(this->x*c, this->y*c, this->z*c);
}

Vec Vec::operator /(float c) const {
       return Vec(this->x/c, this->y/c, this->z/c);
}

float Vec::dot(const Vec& v) const {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vec Vec::cross(const Vec& v) const {
    return Vec(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
}

Vec Vec::normalise() const {
    if (this->getLength() == 0) {
        return *this;
    }
    return *this/this->getLength();
}

float Vec::getLength() const {
    return sqrt(x*x + y*y + z*z);
}

float Vec::getAverage() const {
    return (this->x + this->y + this->z)/3.0f;
}

bool Vec::getIsNormalised() const {
    float length = sqrt(this->dot(*this));
    float epsilon = 0.0001f;
    return (abs(length - 1) <= epsilon);
}

void Vec::formONS(Vec& v, Vec& w) {

    if (abs(this->x) > abs(this->y)) {
        float invertedLength = 1.0f / sqrt(this->x * this->x + this->z * this->z);
        v = Vec(-this->z * invertedLength, 0.0f, this->x * invertedLength); // project to y=0 plane and get normalised vector
    } else {
        float invertedLength = 1.0f / sqrt(this->y * this->y + this->z * this->z);
        v = Vec(0.0, this->z * invertedLength, -this->y * invertedLength); // project to x=0 and get normalised vector
    }
    w = this->cross(v);
}

string Vec::toString() const {
    return 
        "(" 
        + to_string(this->x) + ","
        + to_string(this->y) + ","
        + to_string(this->z)
        + ")";
}

float Vec::distanceTo(const Vec& v) const {
    return (sqrt(pow(this->x - v.x, 2.0) + pow(this->y - v.y, 2.0) + pow(this->z - v.z, 2.0)));
}