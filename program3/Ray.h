//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_RAY_H
#define GLFW_EXAMPLE_RAY_H
#include <stdlib.h>
#include "Vector.h"

//class to hold all the information of a ray
class Ray {
public:
    Vector origin;
    Vector direction;
    int reflectionsRemaining;

    Ray() : origin(Vector()), direction(Vector()), reflectionsRemaining(-1) {
    }

    Ray(Vector origin_, Vector direction_, int reflections) : origin(origin_), reflectionsRemaining(reflections) {
        direction = direction_.normalize();

        //Move intersection slightly forward to avoid intersecting with itself
        origin += (direction / 1000);
    }
};



#endif //GLFW_EXAMPLE_RAY_H
