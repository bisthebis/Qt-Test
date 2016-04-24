#version 450 core

in vec3 VertColor;
in vec2 TexCoords;
uniform vec3 Color;
out vec4 outColor;
uniform sampler2D Text;


void main(){
	vec3 TextColor = texture(Text, TexCoords).xyz;
	outColor = vec4(TextColor*VertColor*Color, 1.0);
}
