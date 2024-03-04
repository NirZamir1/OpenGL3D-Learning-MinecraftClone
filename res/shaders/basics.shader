
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform mat4 mvpMatrix;


out vec4 retcolor;
void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = mvpMatrix *v;
    retcolor = vec4(color,1);
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
//uniform float color;
in vec4 retcolor;
out vec4 FragColor;
void main()
{
    // Interpolate color based on Y-coordinate
    FragColor = retcolor;
};