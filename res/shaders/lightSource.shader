
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
uniform mat4 mvpMatrix;
void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = mvpMatrix * v;
};

#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
out vec4 FragColor;
uniform vec4 lightColor;
out vec4 fragColor;
void main()
{   
    fragColor = lightColor;
};