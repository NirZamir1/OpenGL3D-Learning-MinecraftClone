#shader vertex
#version 440 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 atexCords;
out vec2 texCords;
void main()
{
	texCords = atexCords;
	gl_Position = vec4(pos,-1.0f,1.0f);
};


#shader fragment
#version 330 core
#extension GL_ARB_separate_shader_objects : enable


in vec2 texCords;
out vec4 fragColor;
uniform sampler2D tex;

void main()
{   
	fragColor = texture(tex,texCords);
};