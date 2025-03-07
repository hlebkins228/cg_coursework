#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec3 fragCoord;
uniform vec2 windowSize; 

void main()
{
    float k = windowSize.y / windowSize.x;
    fragCoord = aPos.xyz;
    gl_Position = vec4(aPos.x * k, aPos.y, aPos.z, 2.0);
}
