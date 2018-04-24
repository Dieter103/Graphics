#include "vec4.h"
#include <assert.h>
#include <math.h>
#include <cmath>


bool isEqual(float f1, float f2) {
    //http://www.parashift.com/c++-faq/floating-point-arith.html
    const float epsilon = .0001;
    return std::abs(f1 - f2) <= epsilon * std::abs(f1);
}

//----------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------
vec4::vec4(){
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}

vec4::vec4(float x, float y, float z, float w){
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}

// copy constructor
vec4::vec4(const vec4 &v2){
    *this = v2; //copy contents of v2 into this (shorthand explained by Stephanie)
}

//----------------------------------------------------------------------
// Getters/Setters
//----------------------------------------------------------------------

// Returns the value at index
float vec4::operator[](unsigned int index) const{
    assert(index >= 0 && index <= 3);
    return data[index];
}


// Returns a reference to the value at index
float &vec4::operator[](unsigned int index){
    assert(index >= 0 && index <= 3);
    return data[index];
}

//----------------------------------------------------------------------
// Operator Functions
//----------------------------------------------------------------------

// Assign v2 to this and return it
vec4 &vec4::operator=(const vec4 &v2){
    for(int i = 0; i < 4; i++){
        this->data[i] = v2.data[i];
    }
    return *this;
}

// Test for equality
bool vec4::operator==(const vec4 &v2) const{ //Component-wise comparison
    return (isEqual(this->data[0],v2.data[0]) &&
            isEqual(this->data[1],v2.data[1]) &&
            isEqual(this->data[2],v2.data[2]) &&
            isEqual(this->data[3],v2.data[3]));
}

// Test for inequality
bool vec4::operator!=(const vec4 &v2) const{ //Component-wise comparison
    return !(this->operator==(v2));
}

// Arithmetic:
// e.g. += adds v2 to this and return this (like regular +=)
//      +  returns a new vector that is sum of this and v2
vec4 &vec4::operator+=(const vec4 &v2){
    for(int i = 0; i < 4; i++) {
        this->data[i]+=v2.data[i];
    }
    return *this;
}
vec4 &vec4::operator-=(const vec4 &v2){
    for(int i = 0; i < 4; i++) {
        this->data[i]-=v2.data[i];
    }
    return *this;
}
vec4 &vec4::operator*=(float c){ // multiplication by a scalar
    for(int i = 0; i < 4; i++) {
        this->data[i]*=c;
    }
    return *this;
}

vec4 &vec4::operator/=(float c){ // division by a scalar
    assert(c != 0); //fail if try to divide by 0
    for(int i = 0; i < 4; i++) {
        this->data[i]/=c;
    }
    return *this;
}

vec4 vec4::operator+(const vec4 &v2) const{
    vec4 result = *this;
    return result+=v2;
}
vec4 vec4::operator-(const vec4 &v2) const{
    vec4 result = *this;
    return result-=v2;
}
vec4 vec4::operator*(float c) const{ // multiplication by a scalar
    vec4 result = *this;
    return result*=c;
}
vec4 vec4::operator/(float c) const{             // division by a scalar
    vec4 result = *this;
    return result/=c;
}

// Dot Product
float dot(const vec4 &v1, const vec4 &v2){
    float result = 0;
    for(int i = 0; i < 4; i++) {
        result += (v1[i]*v2[i]);
    }
    return result;
}

// Cross Product
// Compute the result of v1 x v2 using only their X, Y, and Z elements.
// The fourth element of the resultant vector should be 0.
vec4 cross(const vec4 &v1, const vec4 &v2){
    vec4 result = vec4();
    result[0] = (v1[1]*v2[2]) - (v1[2]*v2[1]);
    result[1] = (v1[2]*v2[0]) - (v1[0]*v2[2]);
    result[2] = (v1[0]*v2[1]) - (v1[1]*v2[0]);
    result[3] = 0;
    return result;
}

// Returns the geometric length of the input vector
float length(const vec4 &v){
    //ignore w for length
    float result = 0;
    for(int i = 0; i < 3; i++) {
        result += pow(v[i],2);
    }
    return sqrt(result);
}

// Scalar Multiplication (c * v)
vec4 operator*(float c, const vec4 &v){
    return v*c;
}

// Prints the vector to a stream in a nice format
std::ostream &operator<<(std::ostream &o, const vec4 &v) {
    o << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3];
    return o;
}