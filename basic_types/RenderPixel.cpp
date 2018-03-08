#include "RenderPixel.h"

using namespace std;

// HOW THE FUCK DOES C++11 NOT HAVE A CLAMP FUNCTION?....
template<class T>
const T& clamp(const T& a, const T& lo, const T& hi) {
    return (a<lo?lo:(a>hi?hi:a)); // ternary ops kunt??
}

Pixel::Pixel() : 
    r(0),
    g(0),
    b(0)
{}

Pixel::Pixel(float r, float g, float b) :
    r(r),
    g(g),
    b(b)
{}

Pixel Pixel::operator +(const Pixel& p) const {
    return Pixel(clamp(this->r + p.r, 0.0f, 1.0f), 
                 clamp(this->b + p.b, 0.0f, 1.0f), 
                 clamp(this->g + p.g, 0.0f, 1.0f)
                 );
}

Pixel Pixel::operator -(const Pixel& p) const {
    return Pixel(clamp(this->r - p.r, 0.0f, 1.0f), 
                 clamp(this->b - p.b, 0.0f, 1.0f), 
                 clamp(this->g - p.g, 0.0f, 1.0f)
                 );
}

Pixel Pixel::operator +(const float v) const {
    return Pixel(this->r + v,
                 this->b + v,
                 this->g + v
                 );
}

Pixel Pixel::operator -(const float v) const {
    return Pixel(this->r - v,
                 this->b - v,
                 this->g - v
                 );
}

Pixel Pixel::operator *(const Pixel& p) const {
    return Pixel(this->r * p.r,
                 this->g * p.g,
                 this->b * p.b
                 );
}

Pixel Pixel::operator /(const Pixel& p) const {

}

Pixel Pixel::operator *(const float v) const {
    return Pixel(this->r * v,
                 this->b * v,
                 this->g * v
                 );
}

Pixel Pixel::operator /(const float v) const {
    return Pixel(this->r / v,
                 this->b / v,
                 this->g / v
                 );
}


float Pixel::getAverage() {
    return (this->r + this->g + this->b)/3.0f;
}

Pixel& Pixel::operator +=(const Pixel& p) {
    this->r += p.r;
    this->g += p.g;
    this->b += p.b;
    return *this;
}

Pixel& Pixel::operator -=(const Pixel& p) {
    this->r -= p.r;
    this->g -= p.g;
    this->b -= p.b;
    return *this;
}
