#ifndef _CSCI441_CAMERA_H_
#define _CSCI441_CAMERA_H_

#include <csci441/matrix.h>
#include <csci441/vector.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera {
public:
    Matrix projection;
    Matrix view;
    Vector eye;
    Vector origin;
    Vector up;
    Vector direction;
    int xpos, ypos;


    Camera() : eye(0,0,0), origin(0,0,0), up(0,0,0), direction(0,0,0) {}
    void setAll(Vector eye, Vector look, Vector up){

    }

    Matrix getView() const{
        Matrix mat;
        mat.look_at(eye, direction, up);

        return mat;
    }

    void look_at(Vector pos, Vector direction1,Vector up1){
        eye = pos;
        direction = direction1;
        up = up1;
        view.look_at(eye, direction, up);
    }





};

#endif
