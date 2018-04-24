//
// Created by gross on 4/22/2018.
//

#ifndef GLFW_EXAMPLE_COLOR_H
#define GLFW_EXAMPLE_COLOR_H

#include "bitmap_image.hpp"
/**
 * "NaN To Zero"
 * Converts a NaN value to zero. Otherwise adding values to NaN results in NaN.
 * When adding colors together we usually want to ignore it and use 0 instead.
 */
#define NTZ(X) (isnan((X)) ? 0.0 : (X))
#include <math.h>

class Color {
public:
    double r;
    double g;
    double b;
    rgb_t color;

    double f; // "filter" or "alpha"

    Color() : r(0.0), g(0.0), b(0.0), f(1.0) {}
    Color(double r_, double g_, double b_) : r(r_), g(g_), b(b_), f(1.0) {
        color = make_colour(r, g, b);
    }
    Color operator* (double amount) const {
        Color other;

        other.r = r * amount;
        other.g = g * amount;
        other.b = b * amount;

        return other;
    }

    Color operator+ (Color const &c) const {
        Color other;

        other.r = NTZ(c.r) + NTZ(r);
        other.g = NTZ(c.g) + NTZ(g);
        other.b = NTZ(c.b) + NTZ(b);
        other = maxVals(other);
        other = minVals(other);
        return other;
    }
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
};
#endif //GLFW_EXAMPLE_COLOR_H
