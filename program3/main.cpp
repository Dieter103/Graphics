#include <iostream>


#include "bitmap_image.hpp"
#include <thread>
#include "Sphere.h"
#include "Camera.h"
#include "objLoader.h"
#include "Triangle.h"
#include "RayTracer.h"


using namespace std;


int main(int argc, char** argv) {
    bool debug = false;
    try {
        int choice;
        int x;
        int y;
        string fileName;
        Camera camera;

        //for debugging, skips menu
        if (debug){
            choice =1;
            x = 10000;
            y = 10000;
            fileName = "MoreSpheresLarge";
            camera = Camera(Vector(0,10,-20),Vector(0,1,0), x);

        }else {
            cout << "What would you like to render?" << endl;
            cout << "(1) Spheres" << endl;
            cout << "(2) Dino(Example of triangle rendering)" << endl;
            cout << "Choice: ";
            cin >> choice;
            cout << endl;
            cout << "Enter width: ";
            cin >> x;
            cout << endl;
            cout << "Enter height: ";
            cout << endl;
            cin >> y;
            cout << "Name of file: ";
            cout << endl;
            cin >> fileName;
            camera = Camera(Vector(0,10,-20),Vector(0,1,0), x);

        }
        if(choice == 1) {
            cout<< "Rendering Spheres: "<< x << "x" << y << " BMP, "<< fileName << ".bmp"<<endl;
            bitmap_image image(x, y);
            Object objects;
            vector<Sphere> spheres;
            spheres = objects.world;
            RayTracer rayTracer(image, spheres, camera, fileName);
        }else if (choice == 2) {
            cout<< "Rendering cute lil' dino: "<< x << "x" << y << " BMP, "<< fileName << ".bmp"<<endl;

            bitmap_image image(x, y);

            obj player("../models/biggerDino.obj", 0.6f, 0.6f, 0.60f);
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
            RayTracer rayTracer(image, triangles, camera, fileName);

        }else{
            cout << "That was not a choice" << endl;
        }

    } catch (const std::exception& e) {
        cout<<"ERROR"<<endl;
    }



    // create an image 640 pixels wide by 480 pixels tall









    std::cout << "Success" << std::endl;
}




