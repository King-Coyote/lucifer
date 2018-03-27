#pragma once

#include <pmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <string>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>

using namespace std;

class Vec {
public:
    inline Vec() : vals(_mm_set1_ps(0.0f)) {}
    inline Vec(float fx, float fy, float fz) : vals(_mm_setr_ps(fx, fy, fz, 0.0f)) {}
    inline Vec(const __m128& rhs) : vals(rhs) {}
    ~Vec() {}

    inline void* operator new[](size_t x) { 
        return aligned_alloc(x, 16); 
    }

    inline Vec& operator=(const __m128& rhs) {
        this->vals = rhs;
        return *this;
    }

    inline operator __m128() const {
        return this->vals;
    }

    inline Vec operator+(const Vec& v) const {
        return _mm_add_ps(this->vals, v.vals);
    }

    inline Vec operator-(const Vec& v) const {
        return _mm_sub_ps(this->vals, v.vals);
    }

    inline Vec operator*(const float f) const {
        __m128 scalar = _mm_setr_ps(f, f, f, f);
        return _mm_mul_ps(this->vals, scalar);
    }

    inline Vec operator/(const float f) const {
        float in = 1.0f/f;
        __m128 scalar = _mm_setr_ps(in,in,in,in);
        return _mm_mul_ps(this->vals, scalar);
    }

    inline Vec& operator=(const Vec& v) {
        this->vals = v.vals;
        return *this;
    }

    inline float dot(const Vec& v) const {
        return _mm_cvtss_f32(_mm_dp_ps(vals, v.vals, 0x71));
    }

    inline Vec cross(const Vec& v) const {
        // TODO how does the intrinsic cross product work? 
        // Copy and pasted this bad boy from http://fastcpp.blogspot.com.au/2011/12/simple-vector3-class-with-sse-support.html
        // return _mm_sub_ps(
        //     _mm_mul_ps(_mm_shuffle_ps(this->vals, this->vals, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(v.vals, v.vals, _MM_SHUFFLE(3, 1, 0, 2))), 
        //     _mm_mul_ps(_mm_shuffle_ps(this->vals, this->vals, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(v.vals, v.vals, _MM_SHUFFLE(3, 0, 2, 1)))
        // );
        return Vec(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
    }

    inline Vec normalise() const {
        if (this->getLength() == 0) {
            return *this;
        }
        return *this/this->getLength();
    }

     inline float getLength() const {
        return sqrt(x*x + y*y + z*z);
     }

     inline float getAverage() const {
         return (this->x + this->y + this->z)/3.0f;
     }

    inline bool getIsNormalised() const {
        float length = sqrt(this->dot(*this));
        float epsilon = 0.0001f;
        return (abs(length - 1) <= epsilon);
    }

    inline void formONS(Vec& v, Vec& w) {
        // forms an orthonormal system
        if (abs(this->x) > abs(this->y)) {
            float invertedLength = 1.0f / sqrt(this->x * this->x + this->z * this->z);
            v = Vec(-this->z * invertedLength, 0.0f, this->x * invertedLength); // project to y=0 plane and get normalised vector
        } else {
            float invertedLength = 1.0f / sqrt(this->y * this->y + this->z * this->z);
            v = Vec(0.0, this->z * invertedLength, -this->y * invertedLength); // project to x=0 and get normalised vector
        }
        w = this->cross(v);
    } 

    inline string toString() const {
        return 
        "(" 
        + to_string(this->x) + ","
        + to_string(this->y) + ","
        + to_string(this->z)
        + ")";
    }

    inline float distanceTo(const Vec& v) const {
        return (sqrt(pow(this->x - v.x, 2.0) + pow(this->y - v.y, 2.0) + pow(this->z - v.z, 2.0)));
    }

    union {
        struct {float x, y, z;};
        __m128 vals;
    };
    
private:

    //__m128 vals;
};