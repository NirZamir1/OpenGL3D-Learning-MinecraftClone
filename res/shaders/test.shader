
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 2) in float offset;

void main()
{
    gl_Position = vec4(position.x+offset,position.y,0,1);
};
#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
out vec4 FragColor;
void main()
{   
   FragColor = vec4(1,0,0,1);
};