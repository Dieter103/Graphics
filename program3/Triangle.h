//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_TRIANGLE_H
#define GLFW_EXAMPLE_TRIANGLE_H

#include "Intersection.h"
#include "Light.h"

class Triangle{public:
    Vector v0, v1, v2;
    Light light = Light(Vector(-10,10,-50),0.4);

    Triangle(Vector v0_, Vector v1_, Vector v2_) :
            v0(v0_), v1(v1_), v2(v2_) {
    }

Intersection intersect(Ray ray) {
    Vector e1, e2, h, s, q, normal;
    double a, f, u, v, distance;

    //creating edges vectors from 3 points
    e1 = Vector(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    e2 = Vector(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    //storing the normal for later
    normal = ((v1 - v0).cross(v2 - v0)).normalize();

    //gives orthogonal vector to e2 and direction of Ray
    h = ray.direction.cross(e2);

    // dot product of e1 and h
    a = e1.dot(h);

    //checks to see if ray is parallel
    if (a > -0.00001 && a < 0.00001)
        return Intersection();


    f = 1 / a;
    s = Vector(ray.origin.x - v0.x,
               ray.origin.y - v0.y, ray.origin.z - v0.z);


    u = f * s.dot(h);


    if (u < 0.0 || u > 1.0)
        return Intersection();

    q = s.cross(e1);
    v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return Intersection();

    distance = f * e2.dot(q);

    // Ray Intersection
    if (distance > 0.00001) {
        Vector point = ray.origin + Vector(distance) * ray.direction;
        return Intersection(ray, point, distance, normal, Color(0,1,1));
    }

    return Intersection();
}

    //calculate phong shading model
    Color calculateLighting(const Intersection &intersection, Color intersectionColor) {
        //grab the color of intersected color
        Color color = intersectionColor;
        Color ambientColor = getAmbientLighting(intersection, color);
        Color diffuseAndSpecularColor = getDiffuseAndSpecularLighting(intersection, color);

        return ambientColor + diffuseAndSpecularColor;
    }

    //Multiplies color by a constant and returns for ambient lighting
    Color getAmbientLighting(const Intersection& intersection, const Color& color) {
        return color * 0.2;
    }

    //
    Color getDiffuseAndSpecularLighting(const Intersection& intersection,
                                        const Color& color) {
        //starting diffuse and specular colors
        Color diffuseColor(0.0, 0.0, 0.0);
        Color specularColor(0.0, 0.0, 0.0);

        //set offset to find the distance the light traveled before intersecting
        Vector lightOffset = light.position - intersection.intersection;
        double lightDistance = lightOffset.length();

        //using the offset to save the light direction for passing to isInShadow
        Vector lightDirection = lightOffset.normalize();
        double dotProduct = intersection.normal.dot(lightDirection);

        //If dot product >=0 then face is facing light
        if (dotProduct >= 0.0f) {
            //creating a ray starting at point of intersection using the light direction
            Ray shadowRay = Ray(intersection.intersection, lightDirection,1);

            //set diffuse and specular
            diffuseColor = (diffuseColor + (color * dotProduct)) * light.intensity;
            specularColor = specularColor + getSpecularLighting(intersection);
        }
        return diffuseColor + specularColor;
    }


    //Calculates specular lighting
    Color getSpecularLighting(const Intersection& intersection) {
        Color specularColor(0.0, 0.0, 0.0);

        Vector view = (intersection.ray.origin - intersection.intersection).normalize();
        Vector lightOffset = light.position - intersection.intersection;
        Vector reflected = reflectVector(lightOffset.normalize(), intersection.normal);

        double dot = view.dot(reflected);

        //if dot is less than 0 then then point isn't facing the right way, add no color
        if (dot <= 0) {
            return specularColor;
        }

        //equation for specular
        double specularAmount = pow(dot, 20) * light.intensity;

        specularColor.r = specularAmount;
        specularColor.g = specularAmount;
        specularColor.b = specularAmount;

        return specularColor;
    }

    //finds the reflection direction
    Vector reflectVector(Vector vector, Vector normal) {
        return normal * 2 * vector.dot(normal) - vector;
    }



};
#endif //GLFW_EXAMPLE_TRIANGLE_H
