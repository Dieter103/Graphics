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

#include "shape.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
bool shape = TRUE;


void setShape(bool cube){
    // create
    DiscoCube c;

    Sphere s(20, .5, 0, 0, 1);


//     Cylinder c(20, 1, .2, .4);
    // Cone c(20, 1, .2, .4);
    // Torus c(20, .75, .25, 1, .2, .4);

    if(cube) {
        // copy vertex data
        GLuint VBO1;
        glGenBuffers(1, &VBO1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, c.coords.size() * sizeof(float),
                     &c.coords[0], GL_STATIC_DRAW);
    }else{
        // copy vertex data
        GLuint VBO1;
        glGenBuffers(1, &VBO1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, s.coords.size() * sizeof(float),
                     &s.coords[0], GL_STATIC_DRAW);
    }

//    light vao
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);


    // describe vertex layout
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
                          (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    cout<<"in"<<endl;

}


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
    else if(isPressed(window, GLFW_KEY_C)){shape = TRUE;}
    else if (isPressed(window, GLFW_KEY_S)) { shape = FALSE;}



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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "lab5", NULL, NULL);
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

//    setShape(TRUE);

    // create c
//     Cylinder c(20, 1, .2, .4);
    // Cone c(20, 1, .2, .4);
     Sphere s(20, .5, 0, 0, 1);
    // Torus c(20, .75, .25, 1, .2, .4);
    DiscoCube c;

    // copy vertex data
    GLuint VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, c.coords.size()*sizeof(float),
            &c.coords[0], GL_STATIC_DRAW);


//    light vao
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);


    // describe vertex layout
    GLuint VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // copy vertex data
    GLuint VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, s.coords.size()*sizeof(float),
                 &s.coords[0], GL_STATIC_DRAW);

    // describe vertex layout
    GLuint VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float),
                          (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // setup projection
    Matrix projection;
    projection.perspective(45, 1, .01, 10);

    // setup view
    Vector eye(0, 0, -2);
    Vector origin(0, 0, 0);
    Vector up(0, 1, 0);
    Vector lightPosition( 0,1,-1);



    Matrix camera;
    camera.look_at(eye, origin, up);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // set the matrices
    Matrix model;

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    float deltaTime;
    float lastFrame;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(model, window);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

        GLint lightPos = glGetUniformLocation(shader.id(), "lightPos");
        GLint lightColor = glGetUniformLocation(shader.id(), "lightColor");
        GLint viewPos = glGetUniformLocation(shader.id(), "viewPos");
        Uniform::set(shader.id(), "model", model);
        Uniform::set(shader.id(), "projection", projection);
        Uniform::set(shader.id(), "camera", camera);

        lightPosition = Vector(1.0f + sin(glfwGetTime()) * 2.0f,sin(glfwGetTime() / 2.0f) * 1.0f, lightPosition.z());

        glUniform3f(lightPos, lightPosition.x(),lightPosition.y(),lightPosition.z());
        glUniform3f(lightColor, 1,1,1);
        glUniform3f(viewPos, eye.x(), eye.y(), eye.z());







        // render the cube

        if(shape) {
            glBindVertexArray(VAO1);
            glDrawArrays(GL_TRIANGLES, 0, c.coords.size()*sizeof(float));
        } else{
            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 0, s.coords.size()*sizeof(float));
        }
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, c.coords.size()*sizeof(float));
        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
