//
// Created by gross on 3/29/2018.
//

#ifndef GLFW_EXAMPLE_OBJLOADER_H
#define GLFW_EXAMPLE_OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include <csci441/vector.h>
#include "shape.h"

using namespace std;


class obj{
public:
    std::vector<float> coordinates;
    std::vector<float> vertexNormCoordinates;
    std::vector<float> faceNormCoordinates;

    void loadOBJ(const char * path){

    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Vector> temp_vertices;
    std::vector<Vector> temp_uvs;
    std::vector<Vector> temp_normals;


    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("File cannot be opened\n");
        getchar();

    }

    while( 1 ){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        // else : parse lineHeader

        if ( strcmp( lineHeader, "v" ) == 0 ){
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            Vector vertex = Vector(x, y, z);
            temp_vertices.push_back(vertex);;
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z);
            Vector normal = Vector(x,y,z);
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3];
            unsigned int normalIndex[3];
            unsigned int uvIndex[3];
//            unsigned int uvIndex[3];
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2] );
            if (matches != 3){
                printf("File can't be read\n");
                fclose(file);
                break;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);


        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }
        bool color = true;

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
        int r = 0;
        int g = 1;
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
//        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        Vector vertex = temp_vertices.at(vertexIndex - 1);

        add_vertex(coordinates, vertex.values[0], vertex.values[1], vertex.values[2], r, g, 0 );

    }
    fclose(file);

}


    obj(const char * path){
        loadOBJ(path);
        faceNormCoordinates = calcFaceNormals(coordinates);
        vertexNormCoordinates = calcVertexNormals(coordinates);
    }
};

#endif //GLFW_EXAMPLE_OBJLOADER_H
