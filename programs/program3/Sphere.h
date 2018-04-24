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
    Material* material;
    bool refractive;
    int id;


    Sphere(const Vector& center=Vector(0,0,0),
        float radius=0,
        const Color color=Color(0,0,0), double refractive  = 0) : center(center), radius(radius), color(color), refractive(refractive)
        {
            static int id_seed = 0;
            id = ++id_seed;
        }



    Intersection intersect(Ray ray) const
    {
//        Vector l =  ray.origin-center;
//        float tca = l.dot(ray.direction);
//        if (tca < 0) return Intersection();
//        float d2 = l.dot(l) - tca * tca;
//        if (d2 > radius) return Intersection();
//        float thc = sqrt(radius - d2);
        Vector deltap = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = deltap.dot(ray.direction) * 2;
        double c = deltap.dot(deltap) - (radius * radius);

        double disc = b * b - 4 * a * c;
        if (disc < 0) {
            return Intersection(); // No intersection.
        }

        disc = sqrt(disc);

        double q;
        if (b < 0) {
            q = (-b - disc) * 0.5;
        } else {
            q = (-b + disc) * 0.5;
        }

        double r1 = q / a;
        double r2 = c / q;

        if (r1 > r2) {
            double tmp = r1;
            r1 = r2;
            r2 = tmp;
        }

        double distance = r1;
        if (distance < 0) {
            distance = r2;
        }

        if (distance < 0 || isnan(distance)) {
            return Intersection(); // No intersection.
        }

        Vector point = ray.origin + (ray.direction * distance);
        Vector normal = (point - center).normalize();


        // Normal needs to be flipped if this is a refractive ray.
        if (ray.direction.dot(normal) > 0) {
            normal = normal * -1;
        }


        return Intersection(ray, point, distance, normal, color);
    }


};

#endif //GLFW_EXAMPLE_SPHERE_H
