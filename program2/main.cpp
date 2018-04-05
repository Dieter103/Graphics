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
//#include <models/duck.obj>

#include "shape.h"
#include "model.h"
#include "camera.h"
#include "renderer.h"
#include "objLoader.h"

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//setting constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;


bool smoothShading = true;
bool topDownView = false;
bool firstMouse = true;

Camera camera;
Camera cameraTop;


Vector cameraPos = Vector(0.5, 0, 3);
Vector topCameraPos = Vector(0, 10, 0);
Vector cameraFront = Vector(0, 0, -1);
Vector cameraUp = Vector(0, 1, 0);

float lastX = 1280.0f / 2.0; //cursor position
float lastY = 960.0 / 2.0;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 20.0f;


void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

Matrix processModel(const Matrix &model, GLFWwindow *window) {
    Matrix trans;
    float cameraSpeed = 0.03;
    float cameraSpeed2 = 0.2;

    const float ROT = 1;
    const float SCALE = .05;
    const float TRANS = .05;
    static int oldSpaceState = GLFW_RELEASE;
    int newSpaceState = glfwGetKey(window, GLFW_KEY_SPACE);
    static int oldVState = GLFW_RELEASE;
    int newVState = glfwGetKey(window, GLFW_KEY_V);



    //Movement (Forward, Backward, Side Strafe)
    if (isPressed(window, GLFW_KEY_W)) {
            cameraPos = cameraPos + cameraFront * cameraSpeed;
            topCameraPos = topCameraPos + cameraFront * cameraSpeed;
    } else if (isPressed(window, GLFW_KEY_S)) {
            cameraPos = cameraPos - cameraFront * cameraSpeed;
            topCameraPos = topCameraPos - cameraFront * cameraSpeed;
    } else if (isPressed(window, GLFW_KEY_A)) {
            cameraPos = cameraPos - cameraFront.cross(cameraUp).normalized() * cameraSpeed;
            topCameraPos = topCameraPos - cameraFront.cross(cameraUp).normalized() * cameraSpeed;
    } else if (isPressed(window, GLFW_KEY_D)) {
            cameraPos = cameraPos + cameraFront.cross(cameraUp).normalized() * cameraSpeed;
            topCameraPos = topCameraPos + cameraFront.cross(cameraUp).normalized() * cameraSpeed;
    }
    //Setting Camera View
    else if (newVState == GLFW_RELEASE && oldVState == GLFW_PRESS) {
        topDownView = !topDownView;
    }

    oldSpaceState = newSpaceState;
    oldVState = newVState;

    return trans * model;
}

void processInput(Matrix &model, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    model = processModel(model, window);
}

void errorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow *window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

//    std::vector<float> faceNormCoords = Torus(40, .75, .5, 1, .2, .4).coords;
//    Torus(40, .75, .5, 1, .2, .4).faceNormCoords;
    DiscoCube d;
    Cylinder c(20, 0, 1, 0);
    Sphere s(10, 1, 1, 0, 0);

    Model smoothObj(
            Torus(20, .75, .5, 1, 0, 0).vertexNormCoords,
            Shader("../vert.glsl", "../frag.glsl"));

    std::vector<Vector> vertices;
//    std::vector< glm::vec2 > uvs;
    std::vector<Vector> normals; // Won't be used at the moment.
    obj maze("..\\models\\newMaze1.obj", 0.5f, 0.9f, 0.0f);
    obj player("..\\models\\RoboMiner2.obj", 0.6f, 0.6f, 0.60f);
    obj flag("..\\models\\flag.obj", 1.0f, 0.5f, 0.0f);
//    std::vector<float> coords = *loadOBJ("C:\\Users\\gross\\Documents\\GitHub\\csci441-spring2018\\programs\\program2\\models\\duck.obj");


    Model mazeModel(
            maze.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    Model playerModel(
            player.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    Model flagModel(
            flag.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    flagModel.model.scaleThenTranslate(0.5,0.5,0.5,1.5,-0.5,0.5);



    // make a floor
    Model floor(
            DiscoCube().coords,
            Shader("../vert.glsl", "../frag.glsl"));
    Matrix floor_trans, floor_scale;
    floor_trans.translate(0, -2, 0);
    floor_scale.scale(100, 1, 100);
    floor.model = floor_trans * floor_scale;

    // setup camera
    Matrix projection;

    camera.eye = cameraPos;
    Matrix player_scale, player_translate;
    player_scale.scale(0.3, 0.3, 0.3);
//    player_translate.translate(cameraPos.x(),cameraPos.y(),cameraPos.z());
//    playerModel.model.translate(cameraPos.x(),cameraPos.y(),cameraPos.z());
//    playerModel.model = player_translate*player_scale;



    camera.origin = Vector(0, 0, 0);
    camera.up = cameraUp;
    mazeModel.model.translate(0, -0.5, 0);

    //setup cameraTop
    Matrix projectionTop;
    projectionTop.perspective(fov, SCREEN_WIDTH / SCREEN_HEIGHT, -2, 100);


    cameraTop.projection = projectionTop;
    cameraTop.eye = Vector(camera.eye.x(), 10, camera.eye.y()); //position
    cameraTop.origin = cameraPos; //target
    cameraTop.up = Vector(0, 0, 1);

    Matrix rotate;

    Matrix scaleTrans;
//        scaleTrans.scaleThenTranslate(0.5,0.5,0.5,0,0,0);
    rotate.rotate_y(0.7);


    scaleTrans.scaleThenTranslate(0.3, 0.3, 0.3, cameraPos.x(), cameraPos.y(), cameraPos.z());
//        playerModel.model = scaleTrans;
//    playerModel.model = scaleTrans * rotate;

//    obj.model.scale(0.01,0.01,0.01);
    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // create a renderer
    Renderer renderer;

    // set the light position
    Vector lightPos(3.75f, 3.75f, 4.0f);




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {

        // process input
        if (!smoothShading)
            processInput(mazeModel.model, window);
        else
            processInput(mazeModel.model, window);




//        scaleTrans.scaleThenTranslate(0.5,0.5,0.5,0,0,0);
        rotate.rotate_y(-yaw);


        scaleTrans.scaleThenTranslate(0.3, 0.3, 0.3, cameraPos.x(), cameraPos.y(), cameraPos.z());
//        playerModel.model = scaleTrans;
        playerModel.model = scaleTrans * rotate;

//        playerModel.model.scaleThenTranslate(0.5,0.5,0.5,cameraPos.x(),cameraPos.y(),cameraPos.z()) ;



        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (!topDownView) {
            camera.projection.perspective(45, SCREEN_WIDTH / SCREEN_HEIGHT, .01, 100);
            camera.look_at(cameraPos, cameraPos + cameraFront, camera.up);
            renderer.render(camera, mazeModel, lightPos);
            renderer.render(camera, playerModel, lightPos);
            renderer.render(camera, flagModel, lightPos);
        } else if (topDownView) {
            Matrix projectionUpdate;

            cameraTop.look_at(topCameraPos, cameraPos, cameraTop.up);

            projectionUpdate.perspective(fov, 1, .01, 100);
//
//
            cameraTop.projection = projectionUpdate;

            renderer.render(cameraTop, mazeModel, lightPos);
            renderer.render(cameraTop, playerModel, lightPos);
            renderer.render(cameraTop, flagModel, lightPos);


        }





//        renderer.render(camera, floor, lightPos);
        // render the object and the floor
//        if(!smoothShading) {
//            renderer.render(camera, obj, lightPos);
//            renderer.render(camera, floor, lightPos);
//        }else{
//            renderer.render(camera, smoothObj, lightPos);
//            renderer.render(camera, floor, lightPos);
//        }
        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    Vector front = Vector(0, 0, 0);
    front.values[0] = cos(yaw / 180 * 3.14);
//                      *cos(pitch/180*3.14);
//    front.values[1] = sin(pitch/180*3.14);
    front.values[2] = sin(yaw / 180 * 3.14);
//                      *cos(pitch/180*3.14);
    cameraFront = front.normalized();
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}