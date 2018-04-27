//
// Created by gross on 4/24/2018.
//

#ifndef GLFW_EXAMPLE_OBJECT_H
#define GLFW_EXAMPLE_OBJECT_H

#include "Sphere.h"


class Object{
public:
    //created this class to hold the spheres, and ultimately, triangles too, but ran out of time
    vector<Sphere> world = {
            Sphere(Vector(-50, 0, 0), 1, Color(0,1,0)),
            Sphere(Vector(3, -1, -4), 1, Color(0,1,0), true),
            Sphere(Vector(-3, -1, -4), 1, Color(1,1,1), true),
            Sphere(Vector(0, -2, 2), 3, Color(1,1,1)),
            Sphere(Vector(0, 3,0), 1, Color(0,0,1)),
            Sphere(Vector(0,-6,0), 1, Color(1,0,0)),
            Sphere(Vector(0,0,11), 7, Color(0,1,1)),
            Sphere(Vector(-7, -7, 0), 1, Color(0.294,0,0.5098)),
            Sphere(Vector(7, -7, 0), 1, Color(1,1,0)),
            Sphere(Vector(7, 5, 0), 1, Color(0,1,0)),
            Sphere(Vector(-7, 5, 0), 1, Color(1,0.412,0.706)),

    };
};
#endif //GLFW_EXAMPLE_OBJECT_H
