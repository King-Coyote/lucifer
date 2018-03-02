#include "RenderCamera.h"

RenderCamera::RenderCamera(float width, float height, Vec position, Vec direction) :
    width(width),
    height(height),
    position(position),
    direction(direction),
    up(Vec(0, 0, 1)),
    right(direction.cross(up).normalise())
{}

Vec RenderCamera::pixelToImage(int x, int y) const {
    float alpha = ((float)x / this->width) - 0.5; // alpha and beta are normalisation factors. Here I have assumed FOV is 45 degrees and that the screen varies from 0 to 1.
	float beta = ((float)y / this->height) - 0.5;

	float fovX = 3.141593 / 2.0;
	float fovY = (this->height / this->width)*fovX;

	Vec result = (right*alpha*fovX) + (up*beta*fovY) + this->direction.normalise(); 

	return result;
}

Vec RenderCamera::getPosition() const {
    return this->position;
}