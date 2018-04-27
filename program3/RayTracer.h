//
// Created by gross on 4/22/2018.
//
#include "Camera.h"
#include "Color.h"
#include "Ray.h"
#include "Intersection.h"
#include "Sphere.h"
#include "Object.h"
#include "Triangle.h"
#include <cmath>
#include <future>
#include <atomic>
#include <thread>



#ifndef GLFW_EXAMPLE_RAYTRACER_H
#define GLFW_EXAMPLE_RAYTRACER_H

using namespace std;

class RayTracer{
public:
    Light light = Light(Vector(3,0,-10),0.5);
    Object objects;
    bitmap_image& image;
    vector<Sphere> world;
    vector<Triangle> triangles;
    string fileName;
    int width;
    int height;
    Camera camera;

    //setting the bounds for the window
    int l = -5;
    int r = 5;
    int t = 6;
    int b = -4;

    //Method for Spheres
    RayTracer(bitmap_image& image_, const vector<Sphere>& world_, Camera camera_, string fileName_) : image(image_), world(world_), camera(camera_), fileName("../img/" +fileName_ +".bmp") {

        renderSpheres(image, world);
    }

    //Method for Triangles
    RayTracer(bitmap_image& image_, const vector<Triangle>& world_, Camera camera_, string fileName_) : image(image_), triangles(world_), camera(camera_), fileName("../img/" +fileName_ +".bmp") {
        renderTriangles(image, triangles);
    }

    void renderSpheres(bitmap_image& image, const std::vector<Sphere>& scene) {
        //Construct camera
        camera = Camera(Vector(0, 5, -25), Vector(0, 1, 0), image.width());

        //Start by painting background one color
        for (int y = 0; y<image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                rgb_t color = make_colour(75, 156, 211);
                image.set_pixel(x, y, color);
            }
        }

        //Threading vars
        std::size_t max = image.width() * image.height();
        std::size_t cores = std::thread::hardware_concurrency();
        volatile std::atomic<std::size_t> count(0);
        std::vector<std::future<void>> future_vector;

        //splitting the image up over cores available;
        while (cores--)
            future_vector.emplace_back(
                    std::async([=, &image, &count]() {
                                   while (true) {
                                       std::size_t index = count++;
                                       if (index >= max)
                                           break;
                                       int x = index % image.width();
                                       int y = index / image.width();


                                       for (int i = scene.size() - 1; i >= 0; i--) {
                                           float ui = l + (r - l)*(x + .5) / image.width();
                                           float vj = b + (t - b)*(y + .5) / image.height();
                                           //                            Vector camera = Vector(0,0,-10);
                                           Vector direction = Vector(ui, vj, -10);
                                           Sphere sphere = scene.at(i);
                                           Ray newRay = Ray(camera.position, (direction - camera.position), 1);
                                           Intersection intersect = sphere.intersect(newRay);

                                           bool hit = intersect.didIntersect;
                                           if (hit) {
                                               //                                std::cout << "hit" << std::endl;
                                               calculateLighting(intersect, sphere.color);
                                               rgb_t color = make_colour(
                                                       calculateLighting(intersect, intersect.color).r * 255,
                                                                         calculateLighting(intersect, intersect.color).g * 255,
                                                                         calculateLighting(intersect, intersect.color).b * 255);
                                               image.set_pixel(x, image.height() - y, color);
                                           }
                                       }
                                   }
                               }));

        //wait so image doesn't save before threading starts
        while (count < max) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        //save image
        image.save_image(fileName);

    }

    void renderTriangles(bitmap_image& image, const std::vector<Triangle>& world) {
        l = -12;
        r = 8;
        t = 10;
        b = -10;
        //Start by painting background one color
        for (int y = 0; y<image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                rgb_t color = make_colour(75, 156, 211);
                image.set_pixel(x, y, color);
            }
        }

        //threading vars
        std::size_t max = image.width() * image.height();
        std::size_t cores = std::thread::hardware_concurrency();
        volatile std::atomic<std::size_t> count(0);
        std::vector<std::future<void>> future_vector;

        //splitting image over cores available
        while (cores--)
            future_vector.emplace_back(
                std::async([=, &image, &count]() {
                   while (true)
                   {
                       std::size_t index = count++;
                       if (index >= max)
                           break;
                       int x = index % image.width();
                       int y = index / image.width();

                       for (int i = world.size() - 1; i >= 0; i--) {
                           //each pixel on the image plane
                           float ui = l + (r - l)*(x + .5) / image.width();
                           float vj = b + (t - b)*(y + .5) / image.height();
                           Vector direction = Vector(ui, vj, 0);
                           Triangle triangle = world.at(i);
                           Ray newRay = Ray(camera.position, (direction - camera.position), 2);
                           Intersection intersect = triangle.intersect(newRay);
                           bool hit = intersect.didIntersect;
                           if (hit) {
                               rgb_t color = make_colour(
                                       triangle.calculateLighting(intersect, Color(1, 0, 1)).r * 255,
                                                         triangle.calculateLighting(intersect,
                                                                                    Color(1, 0, 1)).g * 255,
                                                         triangle.calculateLighting(intersect,
                                                                                    Color(1, 0, 1)).b * 255);
                               image.set_pixel(x, image.height() - y, color);
                           }
                       }
                   }
                               }));

        //wait so image doesn't save before threading starts
        while (count < max) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        image.save_image(fileName);
    }

    //calculate phong shading model
    Color calculateLighting(const Intersection &intersection, Color intersectionColor) {
        //grab the color of intersected color
        Color color = intersectionColor;
        Color ambientColor = getAmbientLighting(intersection, color);
        Color diffuseAndSpecularColor = getDiffuseAndSpecularLighting(intersection, color);
        Color reflectedColor = getReflectiveLighting(intersection);

        return ambientColor + diffuseAndSpecularColor +reflectedColor;
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

            //Adds no lighting (color) if in shadow
            if (isInShadow(shadowRay, lightDistance)) {
                return Color(0,0,0);
            }

            //set diffuse and specular
            diffuseColor = (diffuseColor + (color * dotProduct)) * light.intensity;
            specularColor = specularColor + getSpecularLighting(intersection);
        }
        return diffuseColor + specularColor;
    }

    //takes in the light ray starting at the last point of intersection, finds nearest intersection
    bool isInShadow(const Ray& ray, double lightDistance) {
        double distance;
        double oldDistance = objects.world.at(0).intersect(ray).distance;
        Intersection intersection;

        //finds closest intersection
        for(int i= 1; i < objects.world.size(); i++){
            distance = objects.world.at(i).intersect(ray).distance;
            if(distance<oldDistance && (distance>0.11)){
                intersection = objects.world.at(i).intersect(ray);
            }
        }

        //sets closest intersection
        Intersection closestIntersection = intersection;

        //returns true if intersected and isn't closer than first intersection
        return closestIntersection.didIntersect && closestIntersection.distance < lightDistance;
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
        double specularAmount = pow(dot, 200) * light.intensity;

        specularColor.r = specularAmount;
        specularColor.g = specularAmount;
        specularColor.b = specularAmount;

        return specularColor;
    }

    //finds the reflection direction
    Vector reflectVector(Vector vector, Vector normal) {
        return normal * 2 * vector.dot(normal) - vector;
    }

    //returns reflected light
    Color getReflectiveLighting(const Intersection &intersection) {
        Color reflectiveColor;
        int reflectionsRemaining = intersection.ray.reflectionsRemaining;

        //if reflections limit hit or not reflective add no color
        if (reflectionsRemaining <= 0) {
            return Color();
        }

        //finds reflection direction, creates ray from it
        Vector reflected = reflectVector(intersection.ray.origin, intersection.normal);
        Ray reflectedRay(intersection.intersection, reflected, reflectionsRemaining - 1);

        //finds its nearest intersection
        reflectiveColor = castRay(reflectedRay);

        return reflectiveColor;
    }

    //function that casts a ray and finds the nearest intersection
    Color castRay(const Ray& ray) {
        double distance;
        double oldDistance = objects.world.at(0).intersect(ray).distance;
        Intersection intersection;

        //finds nearest intersection
        for(int i= 1; i < objects.world.size(); i++){
            distance = objects.world.at(i).intersect(ray).distance;
            if(distance<oldDistance && (distance>.01)){
                intersection = objects.world.at(i).intersect(ray);
            }
        }

        //if intersection found, return color with calculated lighting
        if (intersection.didIntersect) {
            return calculateLighting(intersection, intersection.getColor());
        } else {
            return Color();
        }
    }
};
#endif //GLFW_EXAMPLE_RAYTRACER_H
