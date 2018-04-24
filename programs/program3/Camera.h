//
// Created by gross on 4/22/2018.
//
#include "Vector.h"

#ifndef GLFW_EXAMPLE_CAMERA_H
#define GLFW_EXAMPLE_CAMERA_H
class Camera {
public:
    Vector position;
    Vector up;
    Vector lookAt;
    Vector w, u, v;
    double screenWidth;

    Camera() {
        position = Vector(0.0, 0.0, 100.0);
        up = Vector(0.0, 1.0, 0.0);
        lookAt = Vector(0.0, 0.0, 0.0);
        screenWidth = 1000;

        calculateWUV();
    }

    Camera(Vector position_, Vector up_, Vector lookAt_, double screenWidth_) :
            position(position_), up(up_), lookAt(lookAt_), screenWidth(screenWidth_) {
        calculateWUV();
    }

    void calculateWUV() {
        w = (lookAt - position).normalize();
        u = up.cross(w).normalize();
        v = w.cross(u);
    }
};
#endif //GLFW_EXAMPLE_CAMERA_H
