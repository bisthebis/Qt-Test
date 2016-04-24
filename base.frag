#version 450 core

layout (location = 0) in vec2 TexCoords;

out vec4 outColor;
uniform sampler2D Text;
uniform vec3 Color;


void main(){
	vec3 TextColor = texture(Text, TexCoords).xyz;
	outColor = vec4(TextColor*Color, 1.0);
}
