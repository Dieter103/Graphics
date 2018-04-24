//
// Created by gross on 3/7/2018.
//
#include "shape.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifndef GLFW_EXAMPLE_VAO_H
#define GLFW_EXAMPLE_VAO_H


class VAO {
public:
    GLuint VertBufferObj;
    GLuint VertArrayObj;
    vector<float> coordinates;
    Matrix model;
    vector<float> boundingBox;
    float xpos;
    float ypos;
    bool isSelected = false;
    VAO(){}
    VAO( vector<float> coords){
        coordinates = coords;


    }
    //set selection
    void setSelect(){
        isSelected = !isSelected;
    }
    //grab model from cursor set model
    void setModel(Matrix mod){
        model = mod;
        xpos = model.values[12];
        ypos = model.values[13];
    };
    //find bounding box
    void boundBox(vector<float> coords){
        float minX = coords.at(0) + xpos;
        float maxX = coords.at(0)+ xpos;
        float minY = coords.at(1) + ypos;
        float maxY = coords.at(1) + ypos;
//        cout<< "FIRST Min: (" << minX << "," << minY << ")" << endl;
        for(int i = 0; i< coords.size()/5; i++ ){
            if ( coords.at(i*5)+ xpos < minX )
                minX = coords.at(i*5)+ xpos;
            if ( coords.at(1+i*5) + ypos< minY )
                minY = coords.at(1 +i*5) + ypos;
            if ( coords.at(i*5)+ xpos > maxX )
                maxX = coords.at(i*5)+ xpos;
            if ( coords.at(1 +i*5) + ypos > maxY )
                maxY = coords.at(1 +i*5) + ypos;
        }
//        cout<< "Min: (" << minX << "," << minY << ")" << endl;
        boundingBox.push_back(minX);
        boundingBox.push_back(minY);
        boundingBox.push_back(maxX);
        boundingBox.push_back(maxY);
    }

    //check if within bounding box
    bool boxCheck(float x, float y){
        boundBox(coordinates);
        bool weAreIn;
        if(x > boundingBox.at(0) && x < boundingBox.at(2)) {
            if (y > boundingBox.at(1) && y < boundingBox.at(3)) {
                weAreIn = true;
            } else {
                weAreIn = false;
            }
        }
        return weAreIn;
    }

    //bind all vertex data
    void bind(){
        glGenBuffers(1, &VertBufferObj);
        glBindBuffer(GL_ARRAY_BUFFER, VertBufferObj);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size()*sizeof(float),
                     &coordinates[0], GL_STATIC_DRAW);
        glGenVertexArrays(1, &VertArrayObj);
        glBindVertexArray(VertArrayObj);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float),
                              (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),
                              (void*)(2*sizeof(float)));
        glEnableVertexAttribArray(1);

    }

    //change color
    void changeColor(float r, float g, float b){
        for (int i = 0; i < coordinates.size()/5; i++){
            coordinates.at(2 + 5*i) += r;
            coordinates.at(3 + 5*i) += g;
            coordinates.at(4 + 5*i) += b;
        }
        bind();
    }


};


#endif //GLFW_EXAMPLE_VBO_H
