#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;

void main()
{
    if (useTexture)
    {
        FragColor = texture(texture1, TexCoord);
    }
    else
    {
        // Set alpha to 0.5 for transparent effect
        FragColor = vec4(Color, 1.0);
    }
}
