//
// Created by gross on 1/16/2018.
//

#ifndef LAB0_VECTOR3_H
#define LAB0_VECTOR3_H



class Vector3 {
public:
    float x;
    float y;
    float z;

    // Constructor
    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {
        // nothing to do here as we've already initialized x, y, and z above
        std::cout << "in Vector3 constructor" << std::endl;
    }

    // Destructor - called when an object goes out of scope or is destroyed
    ~Vector3() {
        // this is where you would release resources such as memory or file descriptors
        // in this case we don't need to do anything
        std::cout << "in Vector3 destructor" << std::endl;
    }
};



#endif //LAB0_VECTOR3_H
