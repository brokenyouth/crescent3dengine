#version 450 core
layout (location = 0) in vec3 InPosition;

out vec3 TexCoords;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;

void main()
{
    TexCoords = InPosition;
    vec4 Pos = ProjectionMatrix * ViewMatrix * vec4(InPosition, 1.0);
    gl_Position = Pos.xyww;
} 