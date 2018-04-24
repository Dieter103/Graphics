#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/matrix3.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "model.h"
#include "camera.h"
#include "renderer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
using namespace glm;

struct Keyframe {
    Vector from;
    Vector to;
    float t;
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

void processInput(GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

void getKeyFrame(Keyframe& keyframe,
        float time, std::vector<Vector> keyframes, int loopLength) {
    float loopTime = fmod(time, loopLength);

    // get the number of key frames
    size_t numFrames = keyframes.size();

    // Convert time to a value between 0 and 1
    // at 0 we're at the beginning of our rotations
    // array, and at 1 we've reach the last one
    float tFrame = fmin(loopTime/loopLength,1);

    // Get two indices into our rotations array
    // that represent our current animation
    unsigned int fromIndex = tFrame*(numFrames);

    // Since we want our animation to cycle
    // mod by the number of frames to
    // interpolate from the first frame to the last frame
    unsigned int toIndex = (fromIndex+1) % numFrames;

    // get the time per frame we will need this too know
    // this for interpolating between frames
    float timePerFrame = loopLength / (float)(numFrames);

    /* fill key frame */

    // compute the amount of time to interpolate between two frames
    keyframe.t = (loopTime - fromIndex*timePerFrame) / timePerFrame;

    // set the values for the two frames
    keyframe.from = keyframes[fromIndex];
    keyframe.to = keyframes[toIndex];
}

mat4 getFromMatrix(vec4& v){
//    mat4 x = (vec4(1, 0 , 0, 0), vec4(0,0,1,0), v.x,
    vec4 v2 = vec4(1, 0 , 0, 0);
    vec4 v3 = vec4(1, 0 , 0, 0);
    vec4 v4 = vec4(1, 0 , 0, 1);
//    Matrix m = (v1,v2,v3,v4);
    return mat4(v1,v2,v3,v4);

}


Matrix getModelMatrixLerp(const Vector& from, const Vector& to, float t) {
    // Part 1 - Variables 'to' and 'from' represent Euler rotations.
    // Construct two matrices, one using 'from' and one using 'to'.
    // Make sure the order of rotations is rotZ*rotY*rotX to match up
    // with later parts.


    // Then linearly interpolate the elements of the matrices using variable 't'.
    // note do not use the glm method
    //  glm::interpolate(glm::mat4, glm::mat4, float)
    // it does not interpolate element wise
    Vector l =  from.scale(t) + to.scale(1-t);
    Matrix rotX;
    rotX.rotate_x(from.x());
    Matrix rotY;
    rotY.rotate_y(from.y());
    Matrix rotZ;
    rotZ.rotate_z(from.z());


    mat4 toMatrix;
    toMatrix = mat4(vec4(1,0,0, to.x()), vec4(0,1,0,to.y()),vec4(0,1,0,to.z()), vec4(0,0,0,1));

    vec4 v1 = vec4(1,0,0, to.x())*t + vec4(1,0,0,from.x())*(t-1);
    vec4 v2 = vec4(0,1,0, to.y())*t + vec4(0,1,0,from.y())*(t-1);
    vec4 v3 = vec4(0,0,1, to.z())*t + vec4(0,0,1,from.z())*(t-1);
    vec4 v4 = vec4(0,0,0, 1)*t + vec4(0,0,0,1)*(t-1);
//    , vec4(0,1,0,to.y()),vec4(0,1,0,to.z()), vec4(0,0,0,1)

    Matrix interpolated = toMatrix*t + toMatrix*(1-t);


    // Return a Matrix.  If you have a glm::mat4,
    // you can construct a Matrix from a glm matrix using the
    // constructor Matrix(glm::mat4)

    Matrix x;
    Matrix y;
    y.values[7] = l.y();
    Matrix z;
    z.values[11] = l.z();

//
//    m1.values[3] = l.x();
//    m1.values[7] = l.y();
//    m1.values[11] = l.z();

    return z*y*x;
}


Matrix getModelMatrixEuler(const Vector& from, const Vector& to, float t) {
    // Part 2 - The next step is to linearly interpolate the two euler
    // angles prior to converting it to a matrix. Create a vec3 variable
    // and use it to store a linearly interpolated combination of from
    // and to.
    //
    // Then construct a matrix using the linearly interpolated Euler angles
    // Notice how the second cube is just being
    // rotated rather than scaled and skewed.

    // Return a Matrix.  If you have a glm::mat4,
    // you can construct a Matrix from a glm matrix using the
    // constructor Matrix(glm::mat4)
    return Matrix();
}


Matrix getModelMatrixQuat(const Vector& from, const Vector& to, float t) {
    // Part 3 - Quaternions are another way to represent orientation.
    // glm has a quaternion data structure called quat. It's constructor
    // can take a vec3 that represents Euler angles. Construct two quaternions
    // using the from and to euler angles.

    // Interpolate the two quaternions using glm::slerp. slerp stands for
    // spherical linear interpolation and is how quaternions can be animated
    // along the shortest path. glm::slerp takes 3 arguments:
    // glm::slerp(glm::quat q1, glm::quat q2, float t)
    // where t is in the range 0-1 and returns a quaternion t percent
    // between q1 and q2

    // The last step is to convert the resulting quaternion into a matrix
    // for use in our fragment shader. Use glm::toMat4(glm::quat) to do so
    // and store the resulting matrix in quatSlerp.

    // Return a Matrix.  If you have a glm::mat4,
    // you can construct a Matrix from a glm matrix using the
    // constructor Matrix(glm::mat4)
    return Matrix();
}

vec4 toGLM (Vector& vec){
    return vec4(vec.x(),vec.y(),vec.z(),vec.w());
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

    // create obj
    Model obj(
            DiscoCube().coords,
            Shader("../vert.glsl", "../frag.glsl"));

    // make a floor
    Model floor(
            DiscoCube().coords,
            Shader("../vert.glsl", "../frag.glsl"));
    Matrix floor_trans, floor_scale;
    floor_trans.translate(0, -6, 0);
    floor_scale.scale(100, 1, 100);
    floor.model = floor_trans*floor_scale;

    // setup camera
    Matrix projection;
    projection.perspective(45, 1, .01, 10);

    Camera camera;
    camera.projection = projection;
    camera.eye = Vector(0, 0, 5);
    camera.origin = Vector(0, 0, 0);
    camera.up = Vector(0, 1, 0);

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // create a renderer
    Renderer renderer;

    // set the light position
    Vector lightPos(3.75f, 3.75f, 4.0f);

    // rotations is an array of key frame Euler angles
    // feel free to change or add more key frames to the rotations
    // array.
    std::vector<Vector> rotations;
    rotations.push_back(Vector(0, 0, 0));
    rotations.push_back(Vector(0, 0, 0));
    rotations.push_back(Vector(-M_PI/3, -M_PI/2, 2*M_PI));
    rotations.push_back(Vector(M_PI/3, M_PI/2, -M_PI));
    rotations.push_back(Vector(M_PI/3, M_PI/2, -M_PI));

    int loopLength = rotations.size();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();

        // process input
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the object and the floor
        renderer.render(camera, floor, lightPos);

        // render the cubes
        Matrix trans;
        Keyframe keyframe;
        getKeyFrame(keyframe, time, rotations, loopLength);

        // matrix lerp
        trans.translate(-2,0,0);
        obj.model =  trans * getModelMatrixLerp(keyframe.from, keyframe.to, keyframe.t);
        renderer.render(camera, obj, lightPos);

        // euler angles
        trans.translate(0,0,0);
        obj.model = trans * getModelMatrixEuler(keyframe.from, keyframe.to, keyframe.t);
        renderer.render(camera, obj, lightPos);

        // quaternions
        trans.translate(2,0,0);
        obj.model = trans * getModelMatrixQuat(keyframe.from, keyframe.to, keyframe.t);
        renderer.render(camera, obj, lightPos);

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
