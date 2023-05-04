#version 330 core

//Position
layout (location = 0) in vec3 aPos;

//Colors
layout (location = 1) in vec3 aColor;

//Texture
layout (location = 2) in vec2 aTex;

//Outputs the color to the fragment shader
out vec3 color;

//Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

//Transformations matrixes 
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uCam;

void main()
{
	//Outputs the position of all vertices
    //gl_Position = uProj * uView * uModel *vec4(aPos, 1.0);
	gl_Position = uCam *vec4(aPos, 1.0);

   //Assigns the colors from the vertex data to color
   color = aColor;

   //Assigns the texture coordinates fromthe vertex data to texCoord
   texCoord = aTex;
}












/*
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
*/