
#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 c;
layout(location = 2) in vec2 texcords;
layout(location = 3) in mat4 modelMatrix;
uniform mat4 vpMatrix;
out vec3 color;
out vec2 texCoords;
out vec3 fragPos;
void main()
{
    vec4 v = vec4(position, 1.0);
    mat4 mvp = vpMatrix * modelMatrix;
    gl_Position = mvp * v;
    fragPos = (modelMatrix * v).xyz;
    texCoords = texcords;
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable
in vec2 texCoords;
in vec3 fragPos;
out vec4 FragColor;
uniform vec4 lightPos;
uniform vec3 cameraPos;
uniform sampler2D tex;
uniform vec4 lightColor;

void main()
{   
    // Interpolate color based on Y-coordinate
    vec4 objectColor =texture(tex,texCoords);
    vec3 vecx = dFdx(fragPos);
    vec3 vecy = dFdy(fragPos);
    vec3 normal = normalize(cross(vecy,vecx));
    vec3 lightVec = normalize(lightPos.xyz - fragPos);
    vec3 eyeVec = normalize(cameraPos - fragPos);
    float diff = max(dot(lightVec,normal),0.0f);
    vec4 diffuse = diff*lightColor;
    vec3 b = 2* dot(normal,lightVec)*normal - lightVec;
    vec4 specular = pow(max(dot(eyeVec, b), 0.0),32) * lightColor * 0.5;
    vec4 ambient = 0.3 * lightColor;
    vec4 result = (ambient+diffuse)* objectColor*0.5 + objectColor*0.3 + specular;
    FragColor = result;
};