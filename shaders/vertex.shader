#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 vertexColor;
uniform vec2 windowSize; 
uniform mat4 transformMatrix;

void main()
{
       float k = windowSize.y / windowSize.x;
       vec4 screenScaleVec = vec4(aPos.x, aPos.y, aPos.z, 1.0);
       gl_Position = screenScaleVec;
       float alpha = -0.5 * gl_Position.z + 0.5;
       // float alpha = 1.0;
       vertexColor = vec4(aColor.rgb, alpha);
}
