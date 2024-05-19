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
vec2 cords[] = vec2[9]
(
	vec2(texCords.x - 1.0f/800.0f, texCords.y+1.0f/800.0f) , vec2(texCords.x, texCords.y+1.0f/800.0f), vec2(texCords.x + 1.0f/800.0f, texCords.y+1.0f/800.0f),
	vec2(texCords.x- 1.0f/800.0f, texCords.y) , vec2(texCords.x, texCords.y), vec2(texCords.x + 1.0f/800.0f, texCords.y),
	vec2(texCords.x - 1.0f/800.0f, texCords.y- 1.0f/800.0f) , vec2(texCords.x, texCords.y- 1.0f/800.0f), vec2(texCords.x + 1.0f/800.0f, texCords.y - 1.0f/800.0f)
);
int kernel[] = int[9]
( 1, 1, 1,
  1, 1, 1,
  1, 1, 1
);
void main()
{   
	vec4 result;
	for(int i =0; i < 9; ++i)
	{
	result += kernel[i] * texture(tex,cords[i])/20;
	}
	result = result;
	fragColor = texture(tex,texCords);
};