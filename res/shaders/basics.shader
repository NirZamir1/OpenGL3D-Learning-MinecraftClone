
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 c;
layout(location = 2) in vec2 texcords;
uniform mat4 mvpMatrix;
uniform mat4 mMatrix;
out vec3 color;
out vec2 texCoords;
out vec3 fragPos;
void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = mvpMatrix * v;
    fragPos = (mMatrix * v).xyz;
    color = c;
    texCoords = texcords;
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
in vec3 color;
in vec2 texCoords;
in vec3 fragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform sampler2D tex;
void main()
{   
    // Interpolate color based on Y-coordinate
    vec4 objectColor =texture(tex,texCoords);
    vec4 lightColor = vec4(1.0f,0.5f,0.5f,1.0f);
    vec3 vecx = dFdx(fragPos);
    vec3 vecy = dFdy(fragPos);
    vec3 normal = normalize(cross(vecy,vecx));
    vec3 lightVec = normalize(lightPos - fragPos);
    vec3 eyeVec = normalize(cameraPos - fragPos);
    float diff = max(dot(lightVec,normal),0.0f);
    vec4 diffuse = diff*lightColor;
    vec3 b = 2* dot(normal,lightVec)*normal - lightVec;
    vec4 specular = pow(max(dot(eyeVec, b), 0.0),32) * lightColor * 0.5;
    vec4 ambient = 0.2 * lightColor;
    vec4 result = (ambient+diffuse)* objectColor + specular;
    FragColor = result;
};