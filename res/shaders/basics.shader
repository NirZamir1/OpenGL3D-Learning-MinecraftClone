
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 c;
layout(location = 2) in vec2 texcords;
uniform mat4 mvpMatrix;

out vec3 color;
out vec2 texCoords;
void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = mvpMatrix * v;
    color = c;
    texCoords = texcords;
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
in vec3 color;
in vec2 texCoords;
out vec4 FragColor;
uniform sampler2D tex;
void main()
{
    // Interpolate color based on Y-coordinate
    vec4 textColor = texture(tex,texCoords);
    FragColor = textColor;
};