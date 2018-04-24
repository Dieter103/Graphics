//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_LIGHT_H
#define GLFW_EXAMPLE_LIGHT_H
#include "Vector.h"

class Light {
public:
    Vector position;
    double intensity;

    Light(Vector position_, double intensity_) :
            position(position_), intensity(intensity_) {}
};
#endif //GLFW_EXAMPLE_LIGHT_H
