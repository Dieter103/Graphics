#version 330 core
in vec3 ourColor;
in vec3 FragPos;


uniform vec3 lightColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(ourColor, 1.0f);
}
