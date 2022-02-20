#version 450 core

out vec4 fragColor;

in vec2 TexCoord;
in vec3 Color;

uniform sampler2D diffuse;


void main()
{
    fragColor = texture(diffuse, TexCoord);
}