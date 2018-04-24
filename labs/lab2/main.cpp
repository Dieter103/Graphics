#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

/**
 * BELOW IS A BUNCH OF HELPER CODE
 * You do not need to understand what is going on with it, but if you want to
 * know, let me know and I can walk you through it.
 */

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* initWindow() {
    GLFWwindow* window;
    if (!glfwInit()) {
        return NULL;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(800, 600, "Lab 2", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

std::string shaderTypeName(GLenum shaderType) {
    switch(shaderType) {
        case GL_VERTEX_SHADER: return "VERTEX";
        case GL_FRAGMENT_SHADER: return "FRAGMENT";
        default: return "UNKNOWN";
    }
}

std::string readFile(const std::string& fileName) {
    std::ifstream stream(fileName);
    std::stringstream buffer;
    buffer << stream.rdbuf();

    std::string source = buffer.str();
    std::cout << "Source:" << std::endl;
    std::cout << source << std::endl;

    return source;
}

/** END OF CODE THAT YOU DON'T NEED TO WORRY ABOUT */

GLuint createShader(const std::string& fileName, GLenum shaderType) {
    std::string source = readFile(fileName);
    const char* src_ptr = source.c_str();

    /** YOU WILL ADD CODE STARTING HERE */
    GLuint shader = 0;
    // create the shader using
    // glCreateShader, glShaderSource, and glCompileShader

    shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &src_ptr, nullptr);
    glCompileShader(shader);


    /** END CODE HERE */

    // Perform some simple error handling on the shader
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderTypeName(shaderType)
            <<"::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = 0;
    /** YOU WILL ADD CODE STARTING HERE */

    // create the program using glCreateProgram, glAttachShader, glLinkProgram
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /** END CODE HERE */

    // Perform some simple error handling
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return shaderProgram;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool debug = false;

int main(void) {


    GLFWwindow* window = initWindow();
    if (!window) {
        std::cout << "There was an error setting up the window" << std::endl;
        return 1;
    }

    //creating vertex list
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    /** YOU WILL ADD DATA INITIALIZATION CODE STARTING HERE */

    /* PART1: ask the user for coordinates and colors, and convert to normalized
     * device coordinates */

    // convert the triangle to an array of floats containing
    // normalized device coordinates and color components.
    // float triangle[] = ...

    // Accept and parse user input for the three points and vertex colors
    if (!debug) {
        cout << "Enter 3 points (enter a point as x,y:r,g,b):" << endl;

        // For each of the three vertices
        for (int i = 0; i <= 12; i+=6) {
            string input;

            cin >> input;

            float values[5];

            string temp;

            int index = 0;

            input.append(",");

            // Read through each character in the string
            for (char k : input) {
                if (k == ',' || k == ':') {
                    values[index] = stof(temp);
                    index++;
                    temp.clear();
                } else {
                    temp.append(1, k);
                }
            }

            //grabbing the temporary values and sticking them in our vertices matrix
            vertices[0+i] = (-1+values[0]*2/width);
            vertices[1+i] = (1-values[1]*2/height);
            vertices[2+i] = 0;
            vertices[3+i] = values[2];
            vertices[4+i] = values[3];
            vertices[5+i] = values[4];

        }
    } else {
        // A set of vertices already set up for quick testing
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    // PART2: map the data

    // create vertex and array buffer objects using
    // glGenBuffers, glGenVertexArrays
    GLuint VBO[1], VAO[1];

    glGenBuffers(1, &VBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // setup triangle using glBindVertexArray, glBindBuffer, GlBufferData


    // setup the attribute pointer for the coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // setup the attribute pointer for the colors
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // both will use glVertexAttribPointer and glEnableVertexAttribArray;





    /** PART3: create the shader program */

    // create the shaders
    // YOU WILL HAVE TO ADD CODE TO THE createShader FUNCTION ABOVE
    GLuint vertexShader = createShader("../vert.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader("../frag.glsl", GL_FRAGMENT_SHADER);

    // create the shader program
    // YOU WILL HAVE TO ADD CODE TO THE createShaderProgram FUNCTION ABOVE
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

    // cleanup the vertex and fragment shaders using glDeleteShader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    /** END INITIALIZATION CODE */



    while (!glfwWindowShouldClose(window)) {
        // you don't need to worry about processInput, all it does is listen
        // for the escape character and terminate when escape is pressed.
        processInput(window);

        /** YOU WILL ADD RENDERING CODE STARTING HERE */
        /** PART4: Implemting the rendering loop */

        // clear the screen with your favorite color using glClearColor
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        // set the shader program using glUseProgram

        glUseProgram(shaderProgram);


//        // update the uniform color
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);



        // bind the vertex array using glBindVertexArray
        glBindVertexArray(VAO[1]);


        // draw the triangles using glDrawArrays
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /** END RENDERING CODE */

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
