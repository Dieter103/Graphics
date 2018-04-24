#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include<conio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include "mat4.h"
#include "vec4.h"
#include <chrono>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;
float translateX = 0.0f;
float translateY = 0.0f;
float rotate = 0.0f;
float rotateX = 1.0f;
float rotateY = 0.0f;
float rotateZ = 0.0f;

///converts mat4 to float[16]
float * toArr(mat4 &fM){

    static float fma[16];

    vec4 t0 = fM[0];
    vec4 t1 = fM[1];
    vec4 t2 = fM[2];
    vec4 t3 = fM[3];



    fma[0] = t0[0];
    fma[1] = t0[1];
    fma[2] = t0[2];
    fma[3] = t0[3];

    fma[4] = t1[0];
    fma[5] = t1[1];
    fma[6] = t1[2];
    fma[7] = t1[3];

    fma[8] = t2[0];
    fma[9] = t2[1];
    fma[10] = t2[2];
    fma[11] = t2[3];

    fma[12] = t3[0];
    fma[13] = t3[1];
    fma[14] = t3[2];
    fma[15] = t3[3];
//    cout << fma[0] << endl;
    return fma;

}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}



void processInput(GLFWwindow *window, Shader &shader) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


int main(void) {
    auto t_start = std::chrono::high_resolution_clock::now();

    GLFWwindow* window;
    mat4 m = mat4();


    cout << "press a key to check its ascii value\nPress ESC to exit\n" << endl;



    glfwSetErrorCallback(errorCallback);
    /* Initialize the library */
    if (!glfwInit()) { return -1; }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lab 4", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);


    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* init the model */
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
    };

    // copy vertex data
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // describe vertex layout
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window, shader);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        mat4 trans;
        mat4 view;
        mat4 projection;
        view = view.lookAt(vec3(4,3,3), vec3(0,0,0), vec3(0,1,0));
        projection = projection.perspMatrix(SCREEN_WIDTH/SCREEN_WIDTH, 0.1f, 100.0f, 45.0f);
//        projection = projection.prjectionMatrix(-1.0f,1.0f,-1.0f,1.0f,0.1f,100.0f);
        trans = mat4(1.0f);
//        vec4 result = trans* vec4(1.0f,0.0f,0.0f,1.0f);

        // Calculate transformation

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        trans = trans.rotate(rotate, rotateX, rotateY, rotateZ)*trans.translate(translateY,translateX,0.0f);
        trans = projection * view * trans;
//        trans = trans.transpose(trans);
//        trans = trans.rotate(time* 180.0f, 0.0f, 0.0f,1.0f);
        vec4 result = trans * vec4(1.0f,2.0f,3.0f, 1.0f);


        float *transPtr = toArr(trans);
        GLint uniTrans = glGetUniformLocation(shader.id(), "trans");
        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, transPtr);


        // activate shader
        shader.use();

        // render the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));


        /* Swap front and back and poll for io events */

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

///key callback function
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwWindowShouldClose(window);
    }
    if (action == GLFW_REPEAT || action == GLFW_PRESS) {
        if(key == GLFW_KEY_W){
            translateY += 0.01f;
        }else if (key == GLFW_KEY_S){
            translateY -= 0.01f;

        }else if(key == GLFW_KEY_A){
            translateX -= 0.01f;

        }else if(key == GLFW_KEY_D){
            translateX += 0.01f;
        }else if(key == GLFW_KEY_U){
            rotate += 5.0f;
        }else if(key == GLFW_KEY_J){
            rotate -= 5.0f;
        }else if(key == GLFW_KEY_1){
            if (rotateX == 0.0f)
                rotateX = 1.0f;
            else{
                rotateX = 0.0f;

            }
        }else if(key == GLFW_KEY_2){
            if (rotateY == 0.0f)
                rotateY = 1.0f;
            else{
                rotateY = 0.0f;

            }
        }else if(key == GLFW_KEY_3){
            if (rotateZ == 0.0f)
                rotateZ = 1.0f;
            else{
                rotateZ = 0.0f;
            }
        }

    }
}