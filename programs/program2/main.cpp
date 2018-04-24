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

//defining callbacks
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//setting constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;


bool smoothShading = true;
bool topDownView = false;
bool firstMouse = true;

Camera camera;
Camera birdsEyeCamera;


Vector cameraPos = Vector(0.5, 0, 3);
Vector topCameraPos = Vector(0.5, 10, 3);
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
    static int oldSpaceState = GLFW_RELEASE;
    int newSpaceState = glfwGetKey(window, GLFW_KEY_SPACE);

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
    //Setting Camera View, using old and new space states so it only presses once
    else if (newSpaceState == GLFW_RELEASE && oldSpaceState == GLFW_PRESS) {
        topDownView = !topDownView;
    }
    oldSpaceState = newSpaceState;

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

    //Importing obj's

    obj maze("..\\models\\newMaze1.obj", 0.5f, 0.9f, 0.0f);
    obj flag("..\\models\\flag.obj", 1.0f, 0.5f, 0.0f);
    obj player("..\\models\\Robominer2.obj", 0.6f, 0.6f, 0.60f);

    //setting the respective models for the obj's
    Model mazeModel(
            maze.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    Model playerModel(
            player.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    Model flagModel(
            flag.coordinates, Shader("../vert.glsl", "../frag.glsl"));
    flagModel.model.scaleThenTranslate(0.5,0.5,0.5,1.5,-0.5,0.5);

    // setup camera
    camera.eye = cameraPos;
    camera.origin = Vector(0, 0, 0);
    camera.up = cameraUp;

    mazeModel.model.translate(0, -0.5, 0);

    //setup bird's eye view camera
    Matrix projectionTop;
    projectionTop.perspective(fov, SCREEN_WIDTH / SCREEN_HEIGHT, -2, 100);

    birdsEyeCamera.projection = projectionTop;
    birdsEyeCamera.eye = Vector(camera.eye.x(), 10, camera.eye.z()); //position
    birdsEyeCamera.origin = cameraPos; //target
    birdsEyeCamera.up = Vector(0, 0, 1);

    //rotation, scale and translate matrices for playerModel
    Matrix rotate,scaleTrans;
    rotate.rotate_y(0.7);

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

        //taking transformations applied to fps camera and applying to playerModel
        rotate.rotate_y(-yaw);
        scaleTrans.scaleThenTranslate(0.3, 0.3, 0.3, cameraPos.x(), cameraPos.y(), cameraPos.z());
        playerModel.model = scaleTrans * rotate;

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Two different rendering modes
        if (!topDownView) {
            camera.projection.perspective(45, SCREEN_WIDTH / SCREEN_HEIGHT, .01, 100);
            camera.look_at(cameraPos, cameraPos + cameraFront, camera.up);

            renderer.render(camera, mazeModel, lightPos);
            renderer.render(camera, playerModel, lightPos);
            renderer.render(camera, flagModel, lightPos);
        } else if (topDownView) {
            Matrix projectionUpdate;
            birdsEyeCamera.look_at(topCameraPos, cameraPos, birdsEyeCamera.up);
            //changing fov via scrolling
            projectionUpdate.perspective(fov, 1, .01, 100);
            birdsEyeCamera.projection = projectionUpdate;

            renderer.render(birdsEyeCamera, mazeModel, lightPos);
            renderer.render(birdsEyeCamera, playerModel, lightPos);
            renderer.render(birdsEyeCamera, flagModel, lightPos);
        }

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

//mouse controls (rotation)
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    // reversing y-coordinates so it's bottom to top
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    Vector front = Vector(0, 0, 0);
    front.values[0] = (float) cos(yaw / 180 * 3.14);
    front.values[2] = (float) sin(yaw / 180 * 3.14);
    cameraFront = front.normalized();
}

//Setting fov with scroll
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}