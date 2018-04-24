#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>
#include <chrono>
#include "VAO.h"

#include "shape.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1280;
Matrix shape;
//Matrix transState;
Matrix stampedModel;
Matrix mouseModel;
double x = 0, y = 0;

int i = 0;
int stampCntr = 0;
int clickCntr = 1;
int selectedCntr = 0;
vector<VAO> VAOList;
vector<VAO> stampedList;
vector<VAO> selectedList;

NewShape n;
bool drawMode = false;
bool selectMode = true;
bool editMode = false;


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

    const float SCALE = .005;
    Matrix projection;

    // SCALE
    if (isPressed(window, '-')) { projection.ortho(-1 - SCALE, 1 + SCALE, -1 - SCALE, 1 + SCALE, -1, 1); }
    else if (isPressed(window, '=')) { projection.ortho(-1 + SCALE, 1 - SCALE, -1 + SCALE, 1 - SCALE, -1, 1); }

    return projection * trans * model;
}

Matrix processPlacementModel(Matrix &model, GLFWwindow *window) {
    Matrix trans;

    const float ROT = 1;
    const float SCALE = .005;
    const float TRANS = .005;

    //setting states for presses so they only press once
    static int oldSpaceState = GLFW_RELEASE;
    static int oldDState = GLFW_RELEASE;
    static int oldSState = GLFW_RELEASE;
    static int oldEState = GLFW_RELEASE;
    static int oldMouseState = GLFW_RELEASE;

    int newSpaceState = glfwGetKey(window, GLFW_KEY_SPACE);
    int newDState = glfwGetKey(window, GLFW_KEY_D);
    int newSState = glfwGetKey(window, GLFW_KEY_S);
    int newEState = glfwGetKey(window, GLFW_KEY_E);
    int mouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    //ROTATE
    if (isPressed(window, GLFW_KEY_U)) { trans.rotate_z(-ROT); }
    else if (isPressed(window, GLFW_KEY_I)) { trans.rotate_z(ROT); }
    else if (isPressed(window, GLFW_KEY_Z)) { trans.scale(1 + SCALE, 1 + SCALE, 1 + SCALE); }
    else if (isPressed(window, GLFW_KEY_X)) { trans.scale(1 - SCALE, 1 - SCALE, 1 - SCALE); }
        //TRANSLATE
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0, TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0, -TRANS, 0); }
    else if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS, 0, 0); }
        //COLOR CONTROLS
    else if (isPressed(window, GLFW_KEY_G)) { VAOList.at(i).changeColor(SCALE, 0, 0); }
    else if (isPressed(window, GLFW_KEY_B)) { VAOList.at(i).changeColor(-SCALE, 0, 0); }
    else if (isPressed(window, GLFW_KEY_H)) { VAOList.at(i).changeColor(0, SCALE, 0); }
    else if (isPressed(window, GLFW_KEY_N)) { VAOList.at(i).changeColor(0, -SCALE, 0); }
    else if (isPressed(window, GLFW_KEY_J)) { VAOList.at(i).changeColor(0, 0, SCALE); }
    else if (isPressed(window, GLFW_KEY_M)) { VAOList.at(i).changeColor(0, 0, -SCALE); }
        //Cycle through primitives
    else if (newSpaceState == GLFW_RELEASE && oldSpaceState == GLFW_PRESS) {
        if (i < VAOList.size() - 1)
            i++;
        else
            i = 0;
    }
        //MOUSE CONTROLS
    else if (mouseState == GLFW_RELEASE && oldMouseState == GLFW_PRESS) {
        //EDIT MODE
        if (editMode) {
            for (int t = 0; t < stampedList.size(); t++) {
                //Checking for click inside bounds of shape
                if (stampedList.at(t).boxCheck(x, y)) {
                    //Sets selection
                    if (!stampedList.at(t).isSelected) {
                        VAO temp;
                        temp = stampedList.at(t);
                        selectedList.push_back(temp);
                        cout << stampedList.at(t).isSelected << endl;
                        stampedList.at(t).setSelect();
                        selectedList.at(selectedCntr).changeColor(1, -2, 1);
                        selectedCntr++;
                    } else {
                        selectedList.clear();
                        for (int x = 0; x < stampedList.size(); x++)
                            stampedList.at(x).setSelect();
                        selectedCntr = 0;
                    }
                }
            }
        }
        //DRAW MODE (USER DEFINED PRIMITIVE)
        if (drawMode) {
            if (clickCntr % 4 != 0) {
                n.clicked(x, y, 0, 1, 0);
                clickCntr++;
            }
            if (clickCntr % 4 == 0) {
                VAO newShapeVAO(n.coords);
                newShapeVAO.bind();
                stampedList.push_back(newShapeVAO);
                clickCntr = 1;
                stampCntr++;
            }
        }
        //STAMP MODE
        else if (selectMode) {
            stampedList.push_back(VAOList.at(i));
            stampedList.at(stampCntr).xpos = x;
            stampedList.at(stampCntr).ypos = y;

            stampCntr++;
        }
    //SET MODES
    } else if (newDState == GLFW_RELEASE && oldDState == GLFW_PRESS) {
        drawMode = true;
        selectMode = false;
        editMode = false;
    } else if (newSState == GLFW_RELEASE && oldSState == GLFW_PRESS) {
        selectMode = !selectMode;
        drawMode = false;
        editMode = false;
    } else if (newEState == GLFW_RELEASE && oldEState == GLFW_PRESS) {
        editMode = true;
        selectMode = false;
        drawMode = false;
    }
    //Changing color in edit mode
    if (editMode) {
        if (isPressed(window, GLFW_KEY_G)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(SCALE, 0, 0);
            }
        } else if (isPressed(window, GLFW_KEY_B)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(-SCALE, 0, 0);
            }
        } else if (isPressed(window, GLFW_KEY_H)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(0, SCALE, 0);
            }
        } else if (isPressed(window, GLFW_KEY_N)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(0, -SCALE, 0);;
            }
        } else if (isPressed(window, GLFW_KEY_J)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(0, 0, SCALE);;
            }
        } else if (isPressed(window, GLFW_KEY_M)) {
            for (int k = 0; k < stampedList.size(); k++) {
                if (stampedList.at(k).isSelected)
                    stampedList.at(k).changeColor(0, 0, -SCALE);
            }
        }

    }
    oldSpaceState = newSpaceState;
    oldDState = newDState;
    oldMouseState = mouseState;
    oldSState = newSState;
    oldEState = newEState;


    return trans * model;
}

void processInput(Matrix &model, Matrix &camera, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    model = processModel(model, window);
    camera = processPlacementModel(camera, window);
}

void errorCallback(int error, const char *description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

//Setting cursor pos
static void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    x = (-1 + xpos * 2 / SCREEN_WIDTH);
    y = (1 - ypos * 2 / SCREEN_HEIGHT);
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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "lab5", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    //Set cursor pos callback
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Create primitives
    Square s;
    Triangle t;
    Circle c(20, 0, 1, 0);


    // describe vertex layout for each shape
    VAO squareVAO(s.coords);
    squareVAO.bind();
    VAOList.push_back(squareVAO);

    VAO triangleVAO(t.coords);
    triangleVAO.bind();
    VAOList.push_back(triangleVAO);


    VAO circleVAO(c.coords);
    circleVAO.bind();
    VAOList.push_back(circleVAO);


    // setup projection
    Matrix projection;
    projection.ortho(-1, 1, -1, 1, -1, 1);



    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        //Draw selection lines
        for (int j = 0; j < selectedList.size(); j++) {
            Uniform::set(shader.id(), "model", selectedList.at(j).model);
            Uniform::set(shader.id(), "projection", projection);
            glBindVertexArray(selectedList.at(j).VertArrayObj);
            glDrawArrays(GL_LINE_LOOP, 0, selectedList.at(j).coordinates.size() * sizeof(float));
        }
        //draw stamps
        for (int j = 0; j < stampedList.size(); j++) {
            Uniform::set(shader.id(), "model", stampedList.at(j).model);
            Uniform::set(shader.id(), "projection", projection);
            glBindVertexArray(stampedList.at(j).VertArrayObj);
            glDrawArrays(GL_TRIANGLES, 0, stampedList.at(j).coordinates.size() * sizeof(float));
        }

        //Setting model to follow cursorpos
        mouseModel.values[12] = x;
        mouseModel.values[13] = y;

        //process inputs before there is any stamps
        if (stampedList.size() == 0) {
            processInput(stampedModel, mouseModel, window);

        }

        //process inputs on stamps and mouse model
        if (selectMode) {
            for (int j = 0; j < stampedList.size(); j++) {
                processInput(stampedList.at(j).model, mouseModel, window);
            }
        } else {
            //only processing input on selected shapes
            for (int j = 0; j < stampedList.size(); j++) {
                processInput(stampedList.at(j).model, mouseModel, window);
                if (stampedList.at(j).isSelected) {
                    processInput(selectedList.at(j).model, stampedList.at(j).model, window);
                    processInput(selectedList.at(j).model, selectedList.at(j).model, window);
                }
            }
        }

        Uniform::set(shader.id(), "model", mouseModel);
        Uniform::set(shader.id(), "projection", projection);
        VAOList.at(i).setModel(mouseModel);

        if (selectMode) {
            glBindVertexArray(VAOList.at(i).VertArrayObj);
            glDrawArrays(GL_TRIANGLES, 0, VAOList.at(i).coordinates.size() * sizeof(float));
        }

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
