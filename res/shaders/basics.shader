
#shader vertex
#version 440 core

in vec3 position;
in vec3 c;
uniform mat4 mvpMatrix;

out vec3 color;
void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = mvpMatrix * v;
    color = c;
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
in vec3 color;
out vec4 FragColor;
void main()
{
    // Interpolate color based on Y-coordinate
    FragColor = vec4(color,1.0);
};