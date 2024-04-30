#pragma once
#include "glm.hpp"
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};
struct VertexTex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texturePos;
};