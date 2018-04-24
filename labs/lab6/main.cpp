#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/matrix3.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "model.h"
#include "camera.h"
#include "renderer.h"
#include "objLoader.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
bool smoothShading = true;
int i = 0;
std::vector<Model> shapeList;
std::vector<Model> smoothShapeList;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

Matrix processModel(const Matrix& model, GLFWwindow *window) {
    Matrix trans;

    const float ROT = 1;
    const float SCALE = .05;
    const float TRANS = .01;
    static int oldSpaceState = GLFW_RELEASE;
    static int oldSState = GLFW_RELEASE;
    int newSpaceState = glfwGetKey(window, GLFW_KEY_SPACE);
    int newSState = glfwGetKey(window, GLFW_KEY_S);



    // ROTATE
    if (isPressed(window, GLFW_KEY_U)) { trans.rotate_x(-ROT); }
    else if (isPressed(window, GLFW_KEY_I)) { trans.rotate_x(ROT); }
    else if (isPressed(window, GLFW_KEY_O)) { trans.rotate_y(-ROT); }
    else if (isPressed(window, GLFW_KEY_P)) { trans.rotate_y(ROT); }
    else if (isPressed(window, '[')) { trans.rotate_z(-ROT); }
    else if (isPressed(window, ']')) { trans.rotate_z(ROT); }
    // SCALE
    else if (isPressed(window, '-')) { trans.scale(1-SCALE, 1-SCALE, 1-SCALE); }
    else if (isPressed(window, '=')) { trans.scale(1+SCALE, 1+SCALE, 1+SCALE); }
    // TRANSLATE
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0, TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0, -TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS, 0, 0); }
    else if (isPressed(window, ',')) { trans.translate(0,0,TRANS); }
    else if (isPressed(window, '.')) { trans.translate(0,0,-TRANS); }
    else if (newSpaceState == GLFW_RELEASE && oldSpaceState == GLFW_PRESS) {
        if (i < shapeList.size() - 1)
            i++;
        else
            i = 0;
    }else if (newSState == GLFW_RELEASE && oldSState == GLFW_PRESS) {
        smoothShading = !smoothShading;
    }

    oldSpaceState = newSpaceState;
    oldSState = newSState;

    return trans * model;
}

void processInput(Matrix& model, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    model = processModel(model, window);
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CSCI441-lab", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

//    std::vector<float> faceNormCoords = Torus(40, .75, .5, 1, .2, .4).coords;
//    Torus(40, .75, .5, 1, .2, .4).faceNormCoords;
    DiscoCube d;
    Cylinder c (20, 0,1,0);
    Sphere s(10,1,1,0,0);
    Cone cone(20,0,0,1);

    Model cylinder(
            c.faceNormCoords
            ,
            Shader("../vert.glsl", "../frag.glsl"));
    Model smoothCylinder(
            c.vertexNormCoords
            ,
            Shader("../vert.glsl", "../frag.glsl"));
    Model discoCube(
            d.vertexNormCoords
            ,
            Shader("../vert.glsl", "../frag.glsl"));
    Model smoothTorus(
            Torus(20, .75, .5, 1, 0, 0).vertexNormCoords
            ,
            Shader("../vert.glsl", "../frag.glsl"));
    Model torus(
            Torus(20, .75, .5, 1, 0, 0).faceNormCoords
            ,
            Shader("../vert.glsl", "../frag.glsl"));
    obj duckObj("..\\models\\duck.obj");
    Model duck(
            duckObj.faceNormCoordinates,            Shader("../vert.glsl", "../frag.glsl"));
    Model smoothDuck(
            duckObj.vertexNormCoordinates,            Shader("../vert.glsl", "../frag.glsl"));
    // make a floor
    Model floor(
            DiscoCube().coords,
            Shader("../vert.glsl", "../frag.glsl"));
    Model smoothCone(
            cone.vertexNormCoords, Shader("../vert.glsl", "../frag.glsl"));
    Model flatCone(
            cone.faceNormCoords, Shader("../vert.glsl", "../frag.glsl"));
    obj dinoObj("..\\models\\dino.obj");

    Model dinoModel(
            dinoObj.faceNormCoordinates,            Shader("../vert.glsl", "../frag.glsl"));
    Model smoothDinoModel(
            dinoObj.vertexNormCoordinates,            Shader("../vert.glsl", "../frag.glsl"));

    shapeList.push_back(cylinder);
    smoothShapeList.push_back(smoothCylinder);


    smoothShapeList.push_back(smoothTorus);
    shapeList.push_back(torus);

    smoothShapeList.push_back(smoothCone);
    shapeList.push_back(flatCone);

    duck.model.scale(0.001,0.001,0.001);
    smoothDuck.model.scale(0.001,0.001,0.001);
    smoothShapeList.push_back(smoothDuck);
    shapeList.push_back(duck);

    dinoModel.model.scale(4,4,4);
    smoothDinoModel.model.scale(4,4,4);
    smoothShapeList.push_back(smoothDinoModel);
    shapeList.push_back(dinoModel);








    Matrix floor_trans, floor_scale;
    floor_trans.translate(0, -2, 0);
    floor_scale.scale(100, 1, 100);
    floor.model = floor_trans*floor_scale;

    // setup camera
    Matrix projection;
    projection.perspective(45, 1, .01, 10);

    Camera camera;
    camera.projection = projection;
    camera.eye = Vector(0, 0, 3);
    camera.origin = Vector(0, 0, 0);
    camera.up = Vector(0, 1, 0);

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // create a renderer
    Renderer renderer;

    // set the light position
    Vector lightPos(3.75f, 3.75f, 4.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
//        for (int j = 0; j< shapeList.size() ; j++) {
//
//        }
        if(!smoothShading) {
            processInput(shapeList.at(i).model, window);
        }
        else
            processInput(smoothShapeList.at(i).model, window);
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the object and the floor
        if(!smoothShading) {
            renderer.render(camera, shapeList.at(i), lightPos);
            renderer.render(camera, floor, lightPos);
        }else{
            renderer.render(camera, smoothShapeList.at(i), lightPos);
            renderer.render(camera, floor, lightPos);
        }
        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
