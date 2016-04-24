#version 450 core


layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 inColor;

layout (location = 0) uniform mat4 projection;

out vec3 VertColor;

void main() {
	gl_Position = projection*vec4(pos, 1.0);
	VertColor = inColor;
}
