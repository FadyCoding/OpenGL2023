#version 330 core

//output of the color in RGBA
out vec4 FragColor;

//Color from the vertex shader
in vec3 color;

void main()
{

   FragColor = vec4(color, 1.0f);
}