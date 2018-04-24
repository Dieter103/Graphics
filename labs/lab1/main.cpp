/*
 * References:
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates
 * http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
 */
#include <iostream>

#include "bitmap_image.hpp"

using namespace std;

class Vector3i {
public:
    int x, y, z;

    Vector3i() : x(0), y(0), z(0) {};
    Vector3i(int x, int y, int z) : x(x), y(y), z(z) {}

    Vector3i add(Vector3i other) {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3i operator+(const Vector3i& other) {
        return add(other);
    }

    Vector3i operator*(const float& other) {
        return {(int) (x * other), (int) (y * other), (int) (z * other)};
    }

    friend ostream& operator<<(ostream& stream, const Vector3i& other) {
        stream << "[X: " << other.x << ", Y: " << other.y << ", Z: " << other.z << "]";
        return stream;
    }
};

class Vector2i {
public:
    int x, y;

    Vector2i() : x(0), y(0) {};
    Vector2i(int x, int y) : x(x), y(y) {}

    Vector2i add(Vector2i other) {
        return {x + other.x, y + other.y};
    }

    Vector2i operator+(const Vector2i& other) {
        return add(other);
    }

    friend ostream& operator<<(ostream& stream, const Vector2i& other) {
        stream << "[X: " << other.x << ", Y: " << other.y << "]";
        return stream;
    }
};

class Vertex {
public:
    Vector2i position;
    Vector3i color;

    Vertex() : position(Vector2i()), color(Vector3i()) {}

    friend ostream& operator<<(ostream& stream, const Vertex& other) {
        stream << other.position << " " << other.color;
        return stream;
    }
};

// Effectively like taking the cross product of a vector in R3 and returning the z-coord
// | i    j    k |
// | v1.x v1.y 0 |
// | v2.x v2.y 0 |
// = v1.x * v1.y - v2.x * v2.y
float crossProduct(Vector2i& v1, Vector2i& v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

bool debug = false;

int main(int argc, char** argv) {
    Vertex vertices[3];

    // Accept and parse user input for the three points and vertex colors
    if (!debug) {
        cout << "Enter 3 points (enter a point as x,y:r,g,b):" << endl;

        // For each of the three vertices
        for (auto &vertex : vertices) {
            string input;

            cin >> input;

            float values[5];

            string temp;

            int index = 0;

            input.append(",");

            // Read through each character in the string
            for (char k : input) {
                if (k == ',' || k == ':') {
                    values[index] = stof(temp);
                    index++;
                    temp.clear();
                } else {
                    temp.append(1, k);
                }
            }

            vertex = Vertex();
            vertex.position.x = (int) values[0];
            vertex.position.y = (int) values[1];
            vertex.color.x = (int) (values[2] * 255);
            vertex.color.y = (int) (values[3] * 255);
            vertex.color.z = (int) (values[4] * 255);
        }
    } else {
        // A set of vertices already set up for quick testing
        vertices[0] = Vertex();
        vertices[0].position = Vector2i(0, 0);
        vertices[0].color = Vector3i(255, 120, 120);
        vertices[1] = Vertex();
        vertices[1].position = Vector2i(0, 480);
        vertices[1].color = Vector3i(120, 255, 120);
        vertices[2] = Vertex();
        vertices[2].position = Vector2i(640, 480);
        vertices[2].color = Vector3i(120, 120, 255);
    }

    for (auto &vertex : vertices) {
        cout << vertex << endl;
    }


    Vector2i bottomRight = Vector2i(1000, 1000);
    Vector2i topLeft = Vector2i();

    // Find bounding box
    for (auto &vertex : vertices) {
        if (vertex.position.x > topLeft.x) {
            topLeft.x = vertex.position.x;
        }
        if (vertex.position.y > topLeft.y) {
            topLeft.y = vertex.position.y;
        }
        if (vertex.position.x < bottomRight.x) {
            bottomRight.x = vertex.position.x;
        }
        if (vertex.position.y < bottomRight.y) {
            bottomRight.y = vertex.position.y;
        }
    }

    // create an image 640 pixels wide by 480 pixels tall
    const int width = 640;
    const int height = 480;
    bitmap_image image(width, height);

    Vector2i vs1 = Vector2i(vertices[1].position.x - vertices[0].position.x, vertices[1].position.y - vertices[0].position.y);
    Vector2i vs2 = Vector2i(vertices[2].position.x - vertices[0].position.x, vertices[2].position.y - vertices[0].position.y);

    for (int x = bottomRight.x; x < topLeft.x; x++) {
        for (int y = bottomRight.y; y < topLeft.y; y++) {
            Vector2i q = Vector2i(x - vertices[0].position.x, y - vertices[0].position.y);

            auto u = crossProduct(q, vs2) / crossProduct(vs1, vs2);
            auto v = crossProduct(vs1, q) / crossProduct(vs1, vs2);
            auto w = 1 - u - v;

            if (u >= 0 && v >= 0 && u + v <= 1) {
                auto color = vertices[0].color * u + vertices[1].color * v + vertices[2].color * w;
                image.set_pixel((unsigned int) x, (unsigned int) y, make_colour((unsigned int) color.x, (unsigned int) color.y, (unsigned int) color.z));
            }
        }
    }

    image.save_image("triangle.bmp");
    std::cout << "Success" << std::endl;
}