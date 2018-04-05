#ifndef _CSCI441_SHAPE_H_
#define _CSCI441_SHAPE_H_

#include <cstdlib>
#include <vector>
#include "../../../lib/csci441/include/csci441/vector.h"

using namespace std;

template <typename T, typename N, typename C>
void add_vertex(T& coords, const N& x, const N& y,
        const C& r, const C& g, const C& b, bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-(rand()%150)/100.;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(1);
    coords.push_back(0);
    coords.push_back(0);
}



class NewShape {
public:
    std::vector<float> coords;
    NewShape(){

    }
    void clicked(float x, float y, float r, float g, float b){
        add_vertex(coords, x, y, r, g, b);
    }

};

class Square {
public:
    std::vector<float> coords;
    Square() : coords{
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,


    }{}

};
class Triangle {
public:
       std::vector<float> coords;
       Triangle() : coords{
               -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f,  0.5f, 0.0f, 1.0f, 0.0f, }{

       }
};

class Circle {
public:
    std::vector<float> coords;
    Circle(unsigned int n, float r, float g, float b) {
        double step_size = 2*M_PI / n;
        double c_x=0;
        double c_y=0;
        double h = 0;
        float radius = .5;

        for (int i = 0; i < n; ++i) {
            // vertex i
            double theta_i = i*step_size;
            double vi_x = radius*cos(theta_i);
            double vi_y = radius*sin(theta_i);

            // vertex i+1
            double theta_ip1 = ((i+1)%n)*step_size;
            double vip1_x = radius*cos(theta_ip1);
            double vip1_y = radius*sin(theta_ip1);

            // add triangle viL, viH, vip1L
            add_vertex(coords, vi_x, vi_y, r, g, b);
            add_vertex(coords, vi_x, vi_y, r, g, b);
            add_vertex(coords, vip1_x, vip1_y, r, g, b);


            // add triangle vip1L, viH, vip1H
            add_vertex(coords, vip1_x, vip1_y, r, g, b);
            add_vertex(coords, vi_x, vi_y, r, g, b);
            add_vertex(coords, vip1_x, vip1_y, r, g, b);

            // add high triangle vi, vip1, 0
            add_vertex(coords, vip1_x, vip1_y, r, g, b);
            add_vertex(coords, vi_x, vi_y, r, g, b);
            add_vertex(coords, c_x, c_y, r, g, b);

            // // add low triangle vi, vip1, 0
            add_vertex(coords, vip1_x, vip1_y, r, g, b);
            add_vertex(coords, c_x, c_y, r, g, b);
            add_vertex(coords, vi_x, vi_y, r, g, b);
        }
    }
};



#endif
