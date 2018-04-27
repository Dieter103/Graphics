//
// Created by gross on 4/22/2018.
//

#ifndef GLFW_EXAMPLE_COLOR_H
#define GLFW_EXAMPLE_COLOR_H

#include "bitmap_image.hpp"
#include <math.h>

//color class to hold and perform color operations
class Color {
public:
    double r;
    double g;
    double b;
    rgb_t color;

    Color() : r(0.0), g(0.0), b(0.0){}
    Color(double r_, double g_, double b_) : r(r_), g(g_), b(b_){
        color = make_colour(r, g, b);
    }

    //multiply rgb by value, good for ambient lighting
    Color operator* (double amount) const {
        Color other;

        other.r = r * amount;
        other.g = g * amount;
        other.b = b * amount;

        return other;
    }

    //makes it so I can add to a color (lighting, reflections, etc)
    Color operator+ (Color const &c) const {
        Color other;

        other.r = c.r + r;
        other.g = c.g + g;
        other.b = c.b + b;
        other = maxVals(other);
        other = minVals(other);
        return other;
    }

    //Clamping functions
    Color maxVals(Color const other) const{
        double r = (other.r > 1.0) ? 1.0 : other.r;
        double g = (other.g > 1.0) ? 1.0 : other.g;
        double b = (other.b > 1.0) ? 1.0 : other.b;
        return Color(r,g,b);
    }
    Color minVals(Color const other) const{
        double r = (other.r < 0.0) ? 0.0 : other.r;
        double g = (other.g < 0.0) ? 0.0 : other.g;
        double b = (other.b < 0.0) ? 0.0 : other.b;
        return Color(r,g,b);
    }

    //returns rgb_t color
    rgb_t getColor(){
        color = make_colour(r * 255,
                            g * 255,
                            b * 255);
        return color;
    }
};
#endif //GLFW_EXAMPLE_COLOR_H
