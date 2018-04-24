cmake_minimum_required(VERSION 2.8)
project (glfw_example)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../program2/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

include_directories(../glfw/include)
include_directories(../glad/include)
include_directories(../csci441/include)

set(LAB program2)
add_executable(${LAB} main.cpp ../lib/glad/src/glad.c objLoader.h)
target_link_libraries(${LAB} glfw ${GLFW_LIBRARIES})

