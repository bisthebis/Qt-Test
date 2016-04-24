#version 450 core


layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 UVs;

layout (location = 0) uniform mat4 projection;
layout (location = 1) uniform mat4 view;

layout (location = 0) out vec2 TexCoords;

void main() {
	gl_Position = projection*view*vec4(pos, 1.0);
	TexCoords = UVs;
}
