#pragma once

#include <string>

using namespace std;

class Vec {
public: // MEMBERS
    float x;
    float y;
    float z;
    
public: // METHODS
    Vec();
    Vec(float x, float y, float z);

    Vec operator +(const Vec& v) const;
    Vec operator -(const Vec& v) const;
    Vec operator *(float c) const;
    Vec operator /(float c) const;

    float      dot(const Vec& v) const;
    Vec         cross(const Vec& v) const;
    Vec         normalise() const;
    float      getLength() const;
    float      getAverage() const;
    bool        getIsNormalised() const;
    void        formONS(Vec& v, Vec& w); // forms an orthonormal system
    string      toString() const;
};