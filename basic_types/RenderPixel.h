#pragma once

class Pixel {
public: //MEMBERS
    float r;
    float g;
    float b;
public: // METHODS
    Pixel();
    Pixel(float r, float g, float b);

    Pixel operator +(const Pixel& p) const;
    Pixel operator -(const Pixel& p) const;
    Pixel operator +(const float) const;
    Pixel operator -(const float) const;
    Pixel operator *(const Pixel& p) const;
    Pixel operator /(const Pixel& p) const;
    Pixel operator *(const float) const;
    Pixel operator /(const float) const;

    Pixel& operator +=(const Pixel& p);
    Pixel& operator -=(const Pixel& p);
    

    float getAverage();
};