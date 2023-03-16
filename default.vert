#version 330 core

//Position
layout (location = 0) in vec3 aPos;
//Colors
layout (location = 1) in vec3 aColor;

//Outpus the color to the fragment shader
out vec3 color;

//Variable that controls the time
uniform float uTime;

mat3 rotate(float a_degrees)
{
	float a_radians = radians(a_degrees);
	float c = cos(a_radians);
	float s = sin(a_radians);

	return mat3(
		vec3(c, s, 0.0f),
		vec3(-s, c, 0.0f),
		vec3(0.0f, 0.0f, 1.0f)
	);
}

void main()
{
   gl_Position = vec4(rotate(uTime) * aPos, 1.0);
   color = aColor;
}