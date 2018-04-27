//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_SPHERE_H
#define GLFW_EXAMPLE_SPHERE_H
#include "Sphere.h"
#include "Vector.h"
#include "Ray.h"
#include "Color.h"
#include "Intersection.h"
#include "Light.h"
#include <math.h>
class Sphere{
public:
    Vector center;
    double radius;
    Color color;
    double refractivity;
    int id;
    bool checkerboard;


    Sphere(const Vector& center=Vector(0,0,0),
        float radius=0,
        const Color color=Color(0,0,0), bool checkerboard = false) : center(center), radius(radius), color(color), refractivity(refractivity),
                                                                                               checkerboard(checkerboard)
        {
            static int id_seed = 0;
            id = ++id_seed;
        }

    //Checking for intersections
    Intersection intersect(Ray ray) const
    {
        //p vector, direction from camera to center
        Vector p = ray.origin - center;

        //values for quadratic equation
        double a = ray.direction.dot(ray.direction);
        double b = p.dot(ray.direction) * 2;
        double c = p.dot(p) - (radius * radius);

        //determinant
        double disc = b * b - 4 * a * c;

        //if det is less than zero, no intersection
        if (disc < 0) {
            return Intersection(); // No intersection.
        }

        //computing quardatic formula
        disc = sqrt(disc);
        double q;
        if (b < 0) {
            q = (-b - disc) * 0.5;
        } else {
            q = (-b + disc) * 0.5;
        }
        double r1 = q / a;
        double r2 = c / q;

        //finding the positive val (first intersection)
        if (r1 > r2) {
            double tmp = r1;
            r1 = r2;
            r2 = tmp;
        }

        double distance = r1;
        if (distance < 0) {
            distance = r2;
        }

        // No intersection.
        if (distance < 0 || isnan(distance)) {
            return Intersection();
        }

        Vector point = ray.origin + (ray.direction * distance);
        Vector normal = (point - center).normalize();


        // Normal needs to be flipped if this is a refractive ray.
        if (ray.direction.dot(normal) > 0) {
            normal = normal * -1;
        }

        //checks if checkerboard should be applied
        if(this->checkerboard){
            return Intersection(ray, point, distance, normal, getColorCheckerboard(point));
        }else{
            return Intersection(ray, point, distance, normal, color);
        }
    }


    //Procedurally generated Checkerboard pattern
    Color getColorCheckerboard(Vector point) const {
        //set scale of checkerboard pattern
        double scale = 0.5;

        //2 colors to choose from
        Color color1(0,0,0);
        Color color2(1,1,1);

        //going through and checking if value is even
        bool x = (int)((point.x ) / scale) % 2 == 0;
        bool y = (int)((point.y ) / scale) % 2 == 0;
        bool z = (int)((point.z ) / scale) % 2 == 0;

        //exclusive or checking if one (and only one) of the values is true
        if (x ^ y ^ z) {
            return color1;
        } else {
            return color2;
        }
    }
};

#endif //GLFW_EXAMPLE_SPHERE_H
