#include <iostream>

#include <../../glm/glm/glm.hpp>

#include "bitmap_image.hpp"
#include <thread>
#include "mingw.thread.h"
#include "Sphere.h"
#include "Camera.h"
#include "objLoader.h"
#include "Triangle.h"
#include "RayTracer.h"

using namespace std;
obj player("../models/biggerDino.obj", 0.6f, 0.6f, 0.60f);

// build world
//static std::vector<Sphere> world = {
//        Sphere(Vector(0, 0, 0), 1, Color(1,0,0)),
//        Sphere(Vector(0, 0, 3), 2, Color(0,1,0)),
//        Sphere(Vector(2.5, 0, 4), 1, Color(0,0,1)),
//        Sphere(Vector(-2.5,0,4), 1, Color(1,0,0))//        Sphere(Vector(-2, 1, 1), 1, Color(1,1,0)),
//
//};



struct Viewport {
    glm::vec2 min;
    glm::vec2 max;


    Viewport(const glm::vec2& min, const glm::vec2& max)
        : min(min), max(max) {}
};

//struct Sphere {
//    int id;
//    glm::vec3 center;
//    glm::vec3 color;
//    float radius;
//
//    Sphere(const glm::vec3& center=glm::vec3(0,0,0),
//            float radius=0,
//            const glm::vec3& color=glm::vec3(0,0,0)) : center(center), radius(radius), color(color)
//        {
//            static int id_seed = 0;
//            id = ++id_seed;
//        }
//
//    bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t0, float &t1) const
//    {
//        glm::vec3 l =  rayorig-center;
//        float tca = glm::dot(l,raydir);
////        cout<<tca<<endl;
//        if (tca < 0) return false;
//        float d2 = glm::dot(l,l) - tca * tca;
//        if (d2 > radius) return false;
//        float thc = sqrt(radius - d2);
////        t0 = tca - thc;
////        t1 = tca + thc;
//
//        return true;
//    }
//
//};

void run(){

}





void render(bitmap_image& image, const std::vector<Sphere>& scene, bool perspective) {
    // TODO: implement ray tracer
    Camera camera = Camera(Vector(0,5,-25),Vector(0,1,0), Vector(0,0,0), 600);

    //setting the bounds for the window
    int l,r,b,t;
    l=-5;
    r=5;
    t=5;
    b=-5;
    float *t1;
    float *t2;


    for(int y=0;y<image.height();y++) {
        for (int x = 0; x < image.width(); x++) {
            rgb_t color = make_colour(75, 156, 211);
            image.set_pixel(x, y, color);
        }
    }



                for(int y=0;y<=image.height();y++){
                    for(int x=0;x<=image.width();x++){

                        for(int i = scene.size()-1; i>=0; i--){
                            float ui = l + (r-l)*(x+.5) / image.width();
                            float vj = b + (t-b)*(y+.5) / image.height();
//                            Vector camera = Vector(0,0,-10);
                            Vector direction = Vector(ui,vj,-10);
                            Sphere sphere = scene.at(i);
                            Ray newRay = Ray(camera.position, (direction-camera.position),1);
                            Intersection intersect = sphere.intersect(newRay);
                            RayTracer raytracer;

                            bool hit = intersect.didIntersect;
                            if (hit) {
//                                std::cout << "hit" << std::endl;
                                raytracer.performLighting(intersect, sphere.color);
                                rgb_t color = make_colour(raytracer.performLighting(intersect, sphere.color).r * 255,
                                                          raytracer.performLighting(intersect, sphere.color).g * 255,
                                                          raytracer.performLighting(intersect, sphere.color).b * 255);
                                image.set_pixel(x, image.height()-y, color);
                            }
                        }

                    }
                }

        image.save_image("../img/before.bmp");




    }

void renderTriangles(bitmap_image& image, const std::vector<Triangle>& world){
    Camera camera = Camera(Vector(0,10,-20),Vector(0,1,0), Vector(0,0,0), 1920);

    int l,r,b,t;
    l=-10;
    r=10;
    t=10;
    b=-10;
    float *t1;
    float *t2;


    for(int y=0;y<image.height();y++) {
        for (int x = 0; x < image.width(); x++) {
            rgb_t color = make_colour(75, 156, 211);
            image.set_pixel(x, y, color);
        }
    }


        for(int y=0;y<=image.height();y++){
            for(int x=0;x<=image.width();x++){

                for(int i = world.size()-1; i>=0; i--){
                    float ui = l + (r-l)*(x+.5) / image.width();
                    float vj = b + (t-b)*(y+.5) / image.height();
//                            Vector camera = Vector(0,0,-10);
                    Vector direction = Vector(ui,vj,0);
                    Triangle triangle = world.at(i);
                    Ray newRay = Ray(camera.position, (direction - camera.position),2);
                    Intersection intersect = triangle.intersect(newRay);

                    bool hit = intersect.didIntersect;
                    if (hit) {
//                        std::cout << "hit" << std::endl;
                        rgb_t color = make_colour(triangle.performLighting(intersect, Color(1,0,1)).r * 255,
                                                  triangle.performLighting(intersect, Color(1,0,1)).g * 255,
                                                  triangle.performLighting(intersect, Color(1,0,1)).b * 255);
                        image.set_pixel(x, image.height()-y, color);

                    }
                }

            }
        }
    image.save_image("../img/modelMoreLightIntensity.bmp");
}






int main(int argc, char** argv) {

    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(600, 400);
    Object objects;
    vector<Sphere> world;
    world = objects.world;


    vector<Triangle> triangles;
    for(int i= 0; i < player.coordinates.size()/9; i++){
        Vector v1 = Vector(player.coordinates.at(i*9),
                           player.coordinates.at(i*9+1),
                           player.coordinates.at(i*9+2));
        Vector v2 = Vector(player.coordinates.at(i*9+3),
                           player.coordinates.at(i*9+4),
                           player.coordinates.at(i*9+5));
        Vector v3 = Vector(player.coordinates.at(i*9+6),
                           player.coordinates.at(i*9+7),
                           player.coordinates.at(i*9+8));
        Triangle t = Triangle(v1,v2,v3);
        triangles.push_back(t);
    }
//    player.coordinates;

    // render the world
//    thread t(&render, image,world, false);
    thread s(&render, image, world, true);
//    thread s(&renderTriangles, image, triangles);
//    t.join();
    s.join();

//    render(image, world, false);

    std::cout << "Success" << std::endl;
}




