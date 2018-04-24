//
// Created by gross on 4/22/2018.
//
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Object.h"

#ifndef GLFW_EXAMPLE_RAYTRACER_H
#define GLFW_EXAMPLE_RAYTRACER_H

class RayTracer{
public:
    Light light = Light(Vector(3,0,-10),0.5);
    Object objects;
    std::vector<Sphere> world = {
            Sphere(Vector(0, 0, 0), 1, Color(1,0,0)),
            Sphere(Vector(0, 0, 3), 2, Color(0,1,0)),
            Sphere(Vector(2.5, 0, 4), 1, Color(0,0,1)),
            Sphere(Vector(-2.5,0,4), 1, Color(1,0,0))//        Sphere(Vector(-2, 1, 1), 1, Color(1,1,0)),

    };
    int width;
    int height;
    int maxReflections;
    int superSamples; // Square root of number of samples to use for each pixel.
    Camera camera;
    double imageScale;
    int depthComplexity;
    double dispersion;
    unsigned long long raysCast;
//    RayTracer(int width_, int height_, int maxReflections_) : width(width_), height(height_),
//                                                 maxReflections(maxReflections_), camera(Camera()),
//                                                 imageScale(1), dispersion(5.0f), raysCast(0){}
    RayTracer(){}
Color castRayForPixel(int x, int y) {
    double rayX = (x - width / 2)/2.0;
    double rayY = (y - height / 2)/2.0;
    double pixelWidth = rayX - (x + 1 - width / 2)/2.0;
    double sampleWidth = pixelWidth / superSamples;
    double sampleStartX = rayX - pixelWidth/2.0;
    double sampleStartY = rayY - pixelWidth/2.0;
    double sampleWeight = 1.0 / (superSamples * superSamples);
    Color color;

    for (int x = 0; x < superSamples; x++) {
        for (int y = 0; y < superSamples; y++) {
            Vector imagePlanePoint = camera.lookAt -
                                     (camera.u * (sampleStartX + (x * sampleWidth)) * imageScale) +
                                     (camera.v * (sampleStartY + (y * sampleWidth)) * imageScale);

            color = castRayAtPoint(imagePlanePoint);
        }
    }

    return color;
}

    Color castRayAtPoint(const Vector& point) {
        Color color;

        for (int i = 0; i < depthComplexity; i++) {
            Ray viewRay(camera.position, point - camera.position, maxReflections);

            if (depthComplexity > 1) {


                viewRay.origin = viewRay.origin;
                viewRay.direction = point - viewRay.origin;
                viewRay.direction = viewRay.direction.normalize();
            }

//            color = castRay(viewRay);
        }

        return color;
    }

//    void castRay(const Ray& ray) {
//        raysCast++;
//        Intersection intersection = ray.origin(ray);
//
//        if (intersection.didIntersect) {
//            return performLighting(intersection);
//        } else {
//            return Color();
//        }
//    }

    Color performLighting(const Intersection& intersection, Color intersectionColor) {
        Color color = intersectionColor;
        Color ambientColor = getAmbientLighting(intersection, color);
        Color diffuseAndSpecularColor = getDiffuseAndSpecularLighting(intersection, color);
        Color reflectedColor = getReflectiveRefractiveLighting(intersection);

        return ambientColor + diffuseAndSpecularColor +reflectedColor;
    }

    Color getAmbientLighting(const Intersection& intersection, const Color& color) {
        return color * 0.2;
    }

    Color getDiffuseAndSpecularLighting(const Intersection& intersection,
                                        const Color& color) {
        Color diffuseColor(0.0, 0.0, 0.0);
        Color specularColor(0.0, 0.0, 0.0);

//        for (vector<Light*>::iterator itr = lights.begin(); itr < lights.end(); itr++) {
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
//    for(int i = 0; i<1; i++){
        if (dotProduct >= 0.0f) {
                Ray shadowRay = Ray(intersection.intersection, lightDirection,1);

                if (isInShadow(shadowRay, lightDistance)) {
                    /**
                     * Position is in shadow of another object - continue with other lights.
                     */
//                    cout<<"shadow"<<endl;
                    return Color(0,0,0);
                }

            diffuseColor = (diffuseColor + (color * dotProduct)) *
                           light.intensity;
            specularColor = specularColor + getSpecularLighting(intersection);

        }
//    }


        return diffuseColor + specularColor;
    }

    bool isInShadow(const Ray& ray, double lightDistance) {
        double distance;
        double oldDistance = objects.world.at(0).intersect(ray).distance;
        Intersection intersection;
        for(int i= 1; i < objects.world.size(); i++){
            distance = objects.world.at(i).intersect(ray).distance;
            if(distance<oldDistance && (distance>0.11)){
                intersection = objects.world.at(i).intersect(ray);
            }

        }
        Intersection closestIntersection = intersection;

        return closestIntersection.didIntersect && closestIntersection.distance < lightDistance;
    }

    Color getSpecularLighting(const Intersection& intersection) {
        Color specularColor(0.0, 0.0, 0.0);
//        double shininess = intersection.endMaterial->getShininess();

//        if (shininess == NOT_SHINY) {
//            /* Don't perform specular lighting on non shiny objects. */
//            return specularColor;
//        }

        Vector view = (intersection.ray.origin - intersection.intersection).normalize();
        Vector lightOffset = light.position - intersection.intersection;
        Vector reflected = reflectVector(lightOffset.normalize(), intersection.normal);

        double dot = view.dot(reflected);

        if (dot <= 0) {
            return specularColor;
        }

        double specularAmount = pow(dot, 200) * light.intensity;

        specularColor.r = specularAmount;
        specularColor.g = specularAmount;
        specularColor.b = specularAmount;

        return specularColor;
    }

    Vector reflectVector(Vector vector, Vector normal) {
        return normal * 2 * vector.dot(normal) - vector;
    }

    Color getReflectiveRefractiveLighting(const Intersection& intersection) {
        double reflectivity = 1;
        double startRefractiveIndex = 2;
        double endRefractiveIndex = 1;
        int reflectionsRemaining = intersection.ray.reflectionsRemaining;

        /**
         * Don't perform lighting if the object is not reflective or refractive or we have
         * hit our recursion limit.
         */
        if (reflectionsRemaining <= 0) {
            return Color();
        }

        // Default to exclusively reflective values.
        double reflectivePercentage = reflectivity;
        double refractivePercentage = 0;

        // Refractive index overrides the reflective property.
//        if (endRefractiveIndex != NOT_REFRACTIVE) {
        reflectivePercentage = getReflectance(intersection.normal,
                                              intersection.ray.direction, startRefractiveIndex, endRefractiveIndex);
//
//        refractivePercentage = 1 - reflectivePercentage;
//        }

        // No ref{ra,le}ctive properties - bail early.
        if (refractivePercentage <= 0 && reflectivePercentage <= 0) {
            return Color();
        }

        Color reflectiveColor;
        Color refractiveColor;

        if (reflectivePercentage > 0) {
            Vector reflected = reflectVector(intersection.ray.origin,
                                             intersection.normal);
            Ray reflectedRay(intersection.intersection, reflected, reflectionsRemaining - 1);
            reflectiveColor = castRay(reflectedRay) * reflectivePercentage;
        }

        if (refractivePercentage > 0) {
            Vector refracted = refractVector(intersection.normal,
                                             intersection.ray.direction, startRefractiveIndex, endRefractiveIndex);
            Ray refractedRay = Ray(intersection.intersection, refracted, 1);

            refractiveColor = castRay(refractedRay) * refractivePercentage;
        }

        return reflectiveColor + refractiveColor;
    }



    double getReflectance(const Vector& normal, const Vector& incident,
                          double n1, double n2) {
        double n = n1 / n2;
        double cosI = -normal.dot(incident);
        double sinT2 = n * n * (1.0 - cosI * cosI);

        if (sinT2 > 1.0) {
            // Total Internal Reflection.
            return 1.0;
        }

        double cosT = sqrt(1.0 - sinT2);
        double r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
        double rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
        return (r0rth * r0rth + rPar * rPar) / 2.0;
    }
    Vector refractVector(const Vector& normal, const Vector& incident,
                         double n1, double n2) {
        double n = n1 / n2;
        double cosI = -normal.dot(incident);
        double sinT2 = n * n * (1.0 - cosI * cosI);

        if (sinT2 > 1.0) {
            std::cerr << "Bad refraction vector!" <<std::endl;
            exit(EXIT_FAILURE);
        }

        double cosT = sqrt(1.0 - sinT2);
        return incident * n + normal * n * cosI - cosT;
    }

    Color castRay(const Ray& ray) {
        double distance;
        double oldDistance = objects.world.at(0).intersect(ray).distance;
        Intersection intersection;
        for(int i= 1; i < objects.world.size(); i++){
            distance = objects.world.at(i).intersect(ray).distance;
            if(distance<oldDistance && (distance>.01)){
                intersection = objects.world.at(i).intersect(ray);
            }

        }

        if (intersection.didIntersect) {
            return performLighting(intersection, intersection.getColor());
        } else {
            return Color();
        }
    }



};
#endif //GLFW_EXAMPLE_RAYTRACER_H
