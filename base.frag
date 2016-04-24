#version 450 core

in vec3 VertColor;
uniform vec3 Color;
out vec4 outColor;

void main(){
	outColor = vec4(VertColor*Color, 1.0);
}