//
// Created by gross on 4/22/2018.
//
#include "Vector.h"

#ifndef GLFW_EXAMPLE_CAMERA_H
#define GLFW_EXAMPLE_CAMERA_H

//camera class holds camera position
class Camera {
public:
    Vector position;
    Vector up;

    double screenWidth;

    Camera(){}
    Camera(Vector position_, Vector up_, double screenWidth_) :
            position(position_), up(up_), screenWidth(screenWidth_) {}

};
#endif //GLFW_EXAMPLE_CAMERA_H
