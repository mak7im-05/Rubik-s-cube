#version 330 core
out vec4 color;

uniform vec3 Colors;

void main(){
    color = vec4(Colors, 1.0f);
}
