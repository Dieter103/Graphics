#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;


uniform mat4 model;
uniform mat4 projection;


out vec3 ourColor;

out vec3 FragPos;
void main() {
    gl_Position = projection * model * vec4(aPos, 1.0);
    ourColor = aColor;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
