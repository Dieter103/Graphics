//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_INTERSECTION_H
#define GLFW_EXAMPLE_INTERSECTION_H


#include <limits>
#include "Vector.h"
#include "Color.h"
#include "Ray.h"

//Class to hold all the information of an intersection
class Intersection {
public:
    Ray ray;
    bool didIntersect;
    Vector intersection;
    double distance;
    double refractivity;
    Vector normal;
    Color color;

    //stores all the important info of an intersection
    Intersection(Ray ray_, Vector intersection_, double distance_, Vector normal_, Color color_) :
            ray(ray_), didIntersect(true), intersection(intersection_), distance(distance_),
            normal(normal_), color(color_){}

    //sets intersection for a non-intersection
    Intersection() : ray(Ray()), didIntersect(false),
                     intersection(Vector()), distance(std::numeric_limits<double>::max()),
                     normal(Vector()){}

    Color getColor() {
        return color;
    };
};

#endif //GLFW_EXAMPLE_INTERSECTION_H
