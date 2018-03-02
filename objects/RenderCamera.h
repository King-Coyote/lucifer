#pragma once

#include "RenderVec.h"

class   RenderCamera {
public: // METHODS
    RenderCamera(float width, float height, Vec position, Vec direction);

    // takes a pixel's coordinates and outputs a position on the image plane.
    // then you can ray cast from the camera pos to that vec to get the ray for tracing.
    Vec pixelToImage(int x, int y) const;
    Vec getPosition() const;
private: // MEMBERS
    // width and height of the image plane.
    float  width;
    float  height;
    Vec    position;
    Vec    direction;
    // absolute world direction for up, and camera's local right vector
    Vec    up;
    Vec    right;
};