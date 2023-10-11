#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexSelector;
layout (location = 4) in float aIsCircle;

out vec4 ourColor;
out vec2 TexCoord;
out float TexSelector;
out float IsCircle;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = aTexCoord;
	TexSelector = aTexSelector;
	IsCircle = aIsCircle;
};