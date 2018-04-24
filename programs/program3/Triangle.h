//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_TRIANGLE_H
#define GLFW_EXAMPLE_TRIANGLE_H

#include "Intersection.h"
#include "Light.h"

class Triangle{public:
    Vector v0, v1, v2;
    Material* material;

    Triangle(Vector v0_, Vector v1_, Vector v2_) :
            v0(v0_), v1(v1_), v2(v2_) {
    }

Intersection intersect(Ray ray) {
    Vector e1, e2, h, s, q, normal;
    double a, f, u, v, distance;

    //creating two vectors from 3 points
    e1 = Vector(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    e2 = Vector(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

    //storing the normal for later
    normal = ((v1 - v0).cross(v2 - v0)).normalize();

    //gives orthogonal vector to e2 and direction of Ray
    h = ray.direction.cross(e2);

    // dot product of e1 and h
    a = e1.dot(h);

    //checks to see if e1 is orthogonal to h, if so, no intersection
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
//    cout<<distance<<endl;

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

    Color performLighting(const Intersection& intersection, Color intersectionColor) {
        Color color = intersectionColor;
        Color ambientColor = getAmbientLighting(intersection, color);
        Color diffuseAndSpecularColor = getDiffuseAndSpecularLighting(intersection, color);
//        Color reflectedColor = getReflectiveRefractiveLighting(intersection);

        return ambientColor + diffuseAndSpecularColor;
    }

    Color getAmbientLighting(const Intersection& intersection, const Color& color) {
        return color * 0.2;
    }

    Color getDiffuseAndSpecularLighting(const Intersection& intersection,
                                        const Color& color) {
        Color diffuseColor(0.0, 0.0, 0.0);
        Color specularColor(0.0, 0.0, 0.0);

//        for (vector<Light*>::iterator itr = lights.begin(); itr < lights.end(); itr++) {
        Light light = Light(Vector(-10,10,-50),0.4);
        Vector lightOffset = light.position - intersection.intersection;
        double lightDistance = lightOffset.length();
        /**
         * TODO: Be careful about normalizing lightOffset too.
         */
        Vector lightDirection = lightOffset.normalize();
        double dotProduct = intersection.normal.dot(lightDirection);

        /**
         * Intersection is facing light.
         */
        if (dotProduct >= 0.0f) {
//                Ray shadowRay = Ray(intersection.intersection, lightDirection, 1,
//                                    intersection.ray.material);

//                if (isInShadow(shadowRay, lightDistance)) {
//                    /**
//                     * Position is in shadow of another object - continue with other lights.
//                     */
//                    continue;
//                }

            diffuseColor = (diffuseColor + (color * dotProduct)) *
                           light.intensity;
            specularColor = specularColor + getSpecularLighting(intersection, &light);
        }


        return diffuseColor + specularColor;
    }

    Color getSpecularLighting(const Intersection& intersection,
                              Light* light) {
        Color specularColor(0.0, 0.0, 0.0);
//        double shininess = intersection.endMaterial->getShininess();

//        if (shininess == NOT_SHINY) {
//            /* Don't perform specular lighting on non shiny objects. */
//            return specularColor;
//        }

        Vector view = (intersection.ray.origin - intersection.intersection).normalize();
        Vector lightOffset = light->position - intersection.intersection;
        Vector reflected = reflectVector(lightOffset.normalize(), intersection.normal);

        double dot = view.dot(reflected);

        if (dot <= 0) {
            return specularColor;
        }

        double specularAmount = pow(dot, 200) * light->intensity;

        specularColor.r = specularAmount;
        specularColor.g = specularAmount;
        specularColor.b = specularAmount;

        return specularColor;
    }

    Vector reflectVector(Vector vector, Vector normal) {
        return normal * 2 * vector.dot(normal) - vector;
    }

};
#endif //GLFW_EXAMPLE_TRIANGLE_H
