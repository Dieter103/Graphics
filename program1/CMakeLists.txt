cmake_minimum_required(VERSION 2.8)
project (glfw_example)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../labs/lib/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

include_directories(../../labs/lib/glfw/include)
include_directories(../../labs/lib/glad/include)
include_directories(../../labs/lib/csci441/include)

set(LAB program1)
add_executable(${LAB} main.cpp ../../labs/lib/glad/src/glad.c)
target_link_libraries(${LAB} glfw ${GLFW_LIBRARIES})

