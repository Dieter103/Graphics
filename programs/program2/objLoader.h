//
// Created by gross on 3/29/2018.
//Thanks to this tutorial: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
//

#ifndef GLFW_EXAMPLE_OBJLOADER_H
#define GLFW_EXAMPLE_OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include <csci441/vector.h>

using namespace std;


class obj{
public:
    vector<float> coordinates;

    void loadOBJ(const char * path, float r, float g, float b){

    printf("Loading OBJ file %s...\n", path);

    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<Vector> temp_vertices;
    vector<Vector> temp_uvs;
    vector<Vector> temp_normals;


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
            temp_vertices.push_back(vertex);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            float x,y,z;
            fscanf(file, "%f %f %f\n", &x, &y, &z);
            Vector normal = Vector(x,y,z);
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            float x,y,z;

            fscanf(file, "%f %f\n", &x, &y, &z);
            Vector uv = Vector(x,y,z);
            temp_uvs.push_back(Vector(uv.x(),uv.y(),uv.z()));
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            int vertexIndex[3] = {0,0,0};
            int normalIndex[3] = {0,0,0};
            int uvIndex[3] = {0,0,0};
            int noUVMatch;
            int allMatch;
//            unsigned int uvIndex[3];

            //Scan file for vertices in the case there are no normal or texture coords or when we have all three
            if (temp_uvs.size() == 0 && temp_normals.size() == 0)
                noUVMatch = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            else
                allMatch = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

            //Just Vertices
            if(noUVMatch == 3){
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
            //All three
            }else if(allMatch == 9 ){
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }else{
                printf("File can't be read\n");
                fclose(file);
                break;
            }

        }else{
            // Probably a comment
            char commentBuffer[1000];
            fgets(commentBuffer, 1000, file);
        }

    }
        bool color = true;

    // For each vertex of each triangle
    for(int i=0; i<vertexIndices.size(); i++ ) {

        // Get the indices of its attributes
        int vertexIndex = vertexIndices[i];

        Vector normal = Vector(0,0,0);
        if (normalIndices.size() ==0)
            normal = Vector(0,0,1);
        else{
            int normalIndex = normalIndices[i];
            normal = temp_normals.at(normalIndex-1);
        }

        // Get the attributes of the index
        Vector vertex = temp_vertices.at(vertexIndex - 1);

        //add the vertex data
        add_vertex(coordinates, vertex.values[0], vertex.values[1], vertex.values[2], r, g, b, normal );
    }
    fclose(file);

}

    //pass in path and color
    obj(const char * path, float r, float g, float b){
        loadOBJ(path, r, g, b);
    }
};


#endif //GLFW_EXAMPLE_OBJLOADER_H
