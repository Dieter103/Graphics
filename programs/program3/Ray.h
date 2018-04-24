//
// Created by gross on 4/23/2018.
//

#ifndef GLFW_EXAMPLE_RAY_H
#define GLFW_EXAMPLE_RAY_H
#include <stdlib.h>
#include "Vector.h"

class Material;

class Ray {
public:
   Vector origin;
   Vector direction;
   Vector fracDir;
   int reflectionsRemaining;
   Material* material;

   Ray() : origin(Vector()), direction(Vector()), reflectionsRemaining(-1){
//      calcFracDirection();
   }

   Ray(Vector origin_, Vector direction_, int reflections): origin(origin_), reflectionsRemaining(reflections){
      direction = direction_.normalize();

      /* Move intersection slightly forward to avoid intersecting with itself. */
//      origin += (direction / 1000);

//      calcFracDirection();
   }

private:
    void calcFracDirection() {
        fracDir.x = 1.0f / direction.x;
        fracDir.y = 1.0f / direction.y;
        fracDir.z = 1.0f / direction.z;
    }};



#endif //GLFW_EXAMPLE_RAY_H
