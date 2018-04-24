//
// Created by gross on 2/13/2018.
//

#include "vec3.h"
#include <cmath>
vec3::vec3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

vec3::vec3(float value)
{
    x = value;
    y = value;
    z = value;
}

vec3::vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3& vec3::add(const vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec3& vec3::subtract(const vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec3& vec3::normalize(const vec3 &other){
    x = x/sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
    y = y/sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
    z = z/sqrt(other.x * other.x + other.y * other.y + other.z * other.z);
    return *this;
}

vec3& vec3::cross(const vec3 &other, const vec3 &other1){
    x = other.y * other1.z - other.z * other1.y;
    y = other.z * other1.x - other.x * other1.z;
    z = other.x * other1.y - other.y * other1.x;
    return *this;
}

vec3& vec3::operator += (const vec3 &other)
{
    return add(other);
}

vec3& vec3::operator -= (const vec3 &other)
{
    return subtract(other);
}

vec3& operator+(vec3 left, const vec3 &right)
{
    return left += right;
}

vec3& operator-(vec3 left, const vec3 &right)
{
    return left -= right;
}

std::ostream& operator<<(std::ostream &stream, const vec3 &vector)
{
    stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
    return stream;
}