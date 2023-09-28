#version 410 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main(){

	mat2 translate = mat2(1.0, 0.0,
					 	  0.0, 1.0);
	// Normalized pixel coordinates (from -1 to 1)
	vec2 uv = TexCoord * translate * 2 - 1;

	float distance = 1 - length(uv);
	if(distance > 0.0)
		distance = 1.0;
	vec4 texColor = texture(ourTexture, TexCoord) * distance;
	FragColor = texColor;
}