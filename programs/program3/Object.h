//
// Created by gross on 4/24/2018.
//

#ifndef GLFW_EXAMPLE_OBJECT_H
#define GLFW_EXAMPLE_OBJECT_H

#include "Sphere.h"

class Object{
public:
    std::vector<Sphere> world = {
            Sphere(Vector(-50, 0, 0), 1, Color(0,1,0)),
            Sphere(Vector(1, 0, -3), 1, Color(0,1,0), true),
            Sphere(Vector(-2, 0, -3), 1, Color(0,1,0), true),

            Sphere(Vector(0, -1, 2), 3, Color(1,1,1)),

            Sphere(Vector(0, 4,0), 1, Color(0,0,1)),
            Sphere(Vector(0,-5,0), 1, Color(1,0,0))//        Sphere(Vector(-2, 1, 1), 1, Color(1,1,0)),

    };


};
#endif //GLFW_EXAMPLE_OBJECT_H
