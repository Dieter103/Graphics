#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#
#include "mat4.h"
#include "vec3.h"



#include <chrono>



using namespace std;

//
//class vec3
//{
//public:
//    float x, y, z;
//public:
//    vec3();
//    vec3(float value);
//    vec3(float x, float y, float z);
//
//    vec3& add(const vec3 &other);
//    vec3& subtract(const vec3 &other);
//
//    vec3& operator+=(const vec3 &other);
//    vec3& operator-=(const vec3 &other);
//
//    friend vec3& operator+(vec3 left, const vec3 &right);
//    friend vec3& operator-(vec3 left, const vec3 &right);
//
//    inline bool operator==(const vec3 &other) const
//    {
//        return x == other.x && y == other.y && z == other.z;
//    }
//    inline bool operator!=(const vec3 &other) const
//    {
//        return !(*this == other);
//    }
//
//    friend std::ostream& operator<<(std::ostream &stream, const vec3 &vector);
//};
//
//vec3::vec3()
//{
//    x = 0.0f;
//    y = 0.0f;
//    z = 0.0f;
//}
//
//vec3::vec3(float value)
//{
//    x = value;
//    y = value;
//    z = value;
//}
//
//vec3::vec3(float x, float y, float z)
//{
//    this->x = x;
//    this->y = y;
//    this->z = z;
//}
//
//vec3& vec3::add(const vec3 &other)
//{
//    x += other.x;
//    y += other.y;
//    z += other.z;
//    return *this;
//}
//
//vec3& vec3::subtract(const vec3 &other)
//{
//    x -= other.x;
//    y -= other.y;
//    z -= other.z;
//    return *this;
//}
//vec3& vec3::operator += (const vec3 &other)
//{
//    return add(other);
//}
//
//vec3& vec3::operator -= (const vec3 &other)
//{
//    return subtract(other);
//}
//
//vec3& operator+(vec3 left, const vec3 &right)
//{
//    return left += right;
//}
//
//vec3& operator-(vec3 left, const vec3 &right)
//{
//    return left -= right;
//}
//
//std::ostream& operator<<(std::ostream &stream, const vec3 &vector)
//{
//    stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
//    return stream;
//}
//
//class mat4
//{
//private:
//    float elements[4 * 4];
//public:
//    mat4();
//    mat4(float diagonal);
//    mat4(float *elements);
//
//    mat4 translate(vec3 vector);
//
//    inline const float* to_array() const
//    {
//        return elements;
//    }
//
//    mat4 operator*=(const mat4 &right);
//    friend mat4 operator*(mat4 left, const mat4 &right);
//public:
//    static mat4 identity();
//    static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
//    static mat4 perspective(float fov, float aspect, float near, float far);
//};
//
//mat4::mat4()
//{
//    for (int i = 0; i < 4 * 4; i++)
//        elements[i] = 0.0f;
//}
//
//mat4::mat4(float diagonal)
//{
//    elements[0 + 0 * 4] = diagonal;
//    elements[1 + 0 * 4] = 0.0f;
//    elements[2 + 0 * 4] = 0.0f;
//    elements[3 + 0 * 4] = 0.0f;
//
//    elements[0 + 1 * 4] = 0.0f;
//    elements[1 + 1 * 4] = diagonal;
//    elements[2 + 1 * 4] = 0.0f;
//    elements[3 + 1 * 4] = 0.0f;
//
//    elements[0 + 2 * 4] = 0.0f;
//    elements[1 + 2 * 4] = 0.0f;
//    elements[2 + 2 * 4] = diagonal;
//    elements[3 + 2 * 4] = 0.0f;
//
//    elements[0 + 3 * 4] = 0.0f;
//    elements[1 + 3 * 4] = 0.0f;
//    elements[2 + 3 * 4] = 0.0f;
//    elements[3 + 3 * 4] = diagonal;
//}
//mat4::mat4(float *elements)
//{
//    for (int i = 0; i < 4 * 4; i++)
//        this->elements[i] = elements[i];
//}
//
//mat4 mat4::translate(vec3 vector)
//{
//    mat4 result(1.0f);
//    elements[0 + 3 * 4] = vector.x;
//    elements[1 + 3 * 4] = vector.y;
//    elements[2 + 3 * 4] = vector.z;
//    return *this * result;
//}
//
//mat4 mat4::identity()
//{
//    return mat4(1.0f);
//}
//
//mat4 mat4::orthographic(float left, float right, float bottom, float top, float n, float f)
//{
//    mat4 result(1.0f);
//
//    result.elements[0 + 0 * 4] = 2.0f / (right - left);
//
//    result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
//
//    result.elements[2 + 2 * 4] = 2.0f / (n - f);
//
//    result.elements[0 + 3 * 4] = (left + right) / (left - right);
//    result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
//    result.elements[2 + 3 * 4] = (f + n) / (f - n);
//
//    return result;
//}
//mat4 mat4::perspective(float fov, float aspect, float near, float far)
//{
//    // TODO: IMPLEMENT!
//    return mat4(1.0f);
//}
//
//mat4 mat4::operator*=(const mat4 &right)
//{
//    return *this * right;
//}
//
//mat4 operator*(mat4 left, const mat4 &right)
//{
//    for (int y = 0; y < 4; y++)
//    {
//        for (int x = 0; x < 4; x++)
//        {
//            float sum = 0.0f;
//            for (int i = 0; i < 4; i++)
//            {
//                sum += left.elements[x + i * 4] * right.elements[i + y * 4];
//            }
//            left.elements[x + y * 4] = sum;
//        }
//    }
//    return left;
//}
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

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void) {
    auto t_start = std::chrono::high_resolution_clock::now();
    /* Initialize the library */
    GLFWwindow* window;
    vec3 v1 = vec3();
    cout<< v1<<endl;
    if (!glfwInit()) {
        return -1;
    }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Lab 3", NULL, NULL);
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
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* init the triangle drawing */
    // define the vertex coordinates of the triangle
    float triangle[] = {
         0.5f,  0.5f, 1.0, 0.0, 0.0,
         0.5f, -0.5f, 1.0, 1.0, 0.0,
        -0.5f,  0.5f, 0.0, 1.0, 0.0,
         0.5f, -0.5f, 1.0, 1.0, 0.0,
        -0.5f, -0.5f, 0.0, 0.0, 1.0,
        -0.5f,  0.5f, 0.0, 1.0, 0.0,
    };

    // create and bind the vertex buffer object and copy the data to the buffer
    GLuint VBO[1];
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // create and bind the vertex array object and describe data layout
    GLuint VAO[1];
    glGenVertexArrays(1, VAO);
    glBindVertexArray(VAO[0]);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // use the shader
        shader.use();

        /** Part 2 animate and scene by updating the transformation matrix */
        vec3 v;
        v = (1.0f,1.0f,0.0f);
        mat4 trans;
        trans = mat4(1.0f);
//        vec4 result = trans* vec4(1.0f,0.0f,0.0f,1.0f);

        // Calculate transformation
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(triangle));
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        trans = trans.translate( sin(time)*0.5f, 0.0f,1.0f);
        cout << trans << endl;
//        trans = trans.rotate(time* 180.0f, 0.0f, 0.0f,1.0f);
        vec4 result = trans * vec4(1.0f,2.0f,3.0f, 1.0f);
        cout << result << endl;

//        mat4 *trans_ptr = &trans;
            float *transPtr = toArr(trans);
//        cout << toArr(trans) <<endl;
        GLint uniTrans = glGetUniformLocation(shader.id(), "trans");
        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, transPtr);

//        uniform color
//        vec3 outColor = vec3(1.0f,0.5f,0.0f);

//        float timeValue = glfwGetTime();
//        float greenValue = sin(time) / 2.0f + 0.5f;
//        GLint vertexColorLocation = glGetUniformLocation(shader.id(), "outColor");
//        glUseProgram(shader.id());
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        //        glUniform4f(vertexColorLocation
//        cout << ((;
        // draw our triangles


        /* Swap front and back * buffers */
        glfwSwapBuffers(window);

        /* Poll for and * process * events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
