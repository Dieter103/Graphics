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

using namespace std;

template <typename T, typename N, typename C>

void add_vert(T& coords, const N& x, const N& y, const N& z,
                const C& r, const C& g, const C& b,
                const Vector& n=Vector(1,0,0), bool with_noise=false) {
    // adding color noise makes it easier to see before shading is implemented
    float noise = 1-with_noise*(rand()%150)/100.;
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(z);
    coords.push_back(r*noise);
    coords.push_back(g*noise);
    coords.push_back(b*noise);

    Vector normal = n.normalized();
    coords.push_back(normal.x());
    coords.push_back(normal.y());
    coords.push_back(normal.z());
}


class obj{
public:
    std::vector<float> coordinates;

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
//            add_vert(x,y,z,1,0,0,1,0,0);
            temp_vertices.push_back(vertex);
//            temp_normals.push_back(Vector(1,0,0));
        }
//        else if ( strcmp( lineHeader, "vt" ) == 0 ){
//            Vector uv;
//            fscanf(file, "%f %f\n", uv.x, uv.y );
//            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
//            temp_uvs.push_back(uv);
//        }
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
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                fclose(file);
                break;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
//            cout<<normalIndex[0]<<endl;


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
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        Vector vertex = temp_vertices.at(vertexIndex - 1);
//        vertex = vertex.normalized();
//        Vector uv = temp_uvs[ uvIndex-1 ];
        Vector normal = temp_normals.at(normalIndex-1);
//        if (color) {
//            color = !color;
//            r = 1;
//            g = 0;
//        }else if(!color){
//            color = !color;
//            r = 0;
//            g = 1;
//        }

        add_vertex(coordinates, vertex.values[0], vertex.values[1], vertex.values[2], r, g, 0, normal );

        // Put the attributes in buffers
//        out_vertices.push_back(vertex);
////        out_uvs     .push_back(uv);
//        out_normals .push_back(normal);

    }
    fclose(file);

}


    obj(const char * path){
        loadOBJ(path);
        calcVertexNormals(coordinates);
    }
};
//class obj{
//public:
//    std::vector<float> coordinates;
//    obj(const char * path){
//        bool b;
//        coordinates = loadOBJ(path);
//        std::cout<<coordinates.at(0)<<std::endl;
//
//    }
//};

#endif //GLFW_EXAMPLE_OBJLOADER_H
