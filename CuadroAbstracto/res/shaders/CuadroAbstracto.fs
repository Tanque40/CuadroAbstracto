#version 410 core
in vec4 ourColor;
in vec2 TexCoord;
in float TexSelector;
in float IsCircle;

out vec4 FragColor;

uniform sampler2D ourTextures[2];

int textSelector = int(TexSelector);
int isCircleBool = int(IsCircle);

void main(){
	mat2 translate = mat2(1.0, 0.0,
					 	  0.0, 1.0);
	// Normalized pixel coordinates (from -1 to 1)
	vec2 uv = TexCoord * translate * 2 - 1;

	float distance = 1 - length(uv);
	if(distance > 0.0)
		distance = 1.0;
	
	vec4 texColor = vec4(1.0);

	if(textSelector == 0)
		texColor = ourColor;
	else
		texColor = texture(ourTextures[textSelector - 1], TexCoord); 

	if(isCircleBool)
		texColor *= distance;

	FragColor = texColor;
} 