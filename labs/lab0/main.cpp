//
// Created by gross on 1/16/2018.
//
#include <iostream>

using namespace std;
//#define Vector3 operator+(Vector3 v, Vector3 v2);


class Vector3 {
public:
    float x;
    float y;
    float z;

    // Constructor
    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {
        // nothing to do here as we've already initialized x, y, and z above
//        std::cout << "in Vector3 constructor" << std::endl;
    }

    //default constructor
    Vector3(): Vector3(0,0,0){}


    // Destructor - called when an object goes out of scope or is destroyed
    ~Vector3() {
        // this is where you would release resources such as memory or file descriptors
        // in this case we don't need to do anything
//        std::cout << "in Vector3 destructor" << std::endl;
    }
};

//Add
Vector3 add(const Vector3& v, const Vector3& v2){
    return Vector3 (v.x + v2.x, v.y + v2.x, v.z + v2.z);
}

//Overloading operators
Vector3 operator+(const Vector3& v, const Vector3& v2){
    return Vector3 (v.x + v2.x, v.y + v2.x, v.z + v2.z);
}

//Overloading stream to make it much easier to print
std::ostream& operator<<(std::ostream& stream, const Vector3& v){
    cout << v.x << ", " << v.y << ", " << v.z << endl;
    return stream;
};

std::ostream& operator<<(std::ostream& stream, const Vector3 array[]){
    for(int i = 0; i< sizeof(array); i++){
        cout << array[i].x << ", " << array[i].y << ", " << array[i].z << endl;
    }
    return stream;
};


int main(int argc, char** argv) {
    string input;


//    cout << "Hello World!" << endl;

//    //Print all command line args
//    for(int i = 1; i < argc; i++){
//        cout << argv[i] << ", ";
//    }
//    cout << endl << "Enter Name: " << endl;
//
//    cin >> input;
//
//    cout << "Hello <" << input << ">, you disgust me" << endl;
//
//    cout << input;





    Vector3 a(1,2,3);
    Vector3 b(4,5,6);

    Vector3 c = add(a,b);

    cout << c.x << ", " << c.y << ", " << c.z << endl;

    Vector3 v(1,2,3);
    Vector3 v2(4,5,6);

    Vector3 v3 = v + v2;
    cout << v3.x << ", " << v3.y << ", " << v3.z << endl;
    cout << v+v2 << std::endl;

    //Part 7
    Vector3* p = new Vector3 (0,0,0);

    p -> y = 5;
    cout << p << endl;
    delete p;

    Vector3 p1 = Vector3 (0,0,0);
    p1.y = 5;
    cout << p1 << endl;



//    delete pointer_to_p;


//    std::cout << v+v2 << std::endl;

    Vector3 array[10];

    Vector3* ptr = new Vector3[10];
    for(int i = 0; i < sizeof(ptr); i++){
        array[i].y = 5;
    }

    cout << array << endl;

//    delete [] ptr;



}