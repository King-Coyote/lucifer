#pragma once

#include <string>
#include "RenderVec.h"

using namespace std;

class Ray {
public: // MEMBERS
    Vec o;
    Vec d;

public: // METHODS
    Ray(Vec o, Vec d);

    string toString();
};