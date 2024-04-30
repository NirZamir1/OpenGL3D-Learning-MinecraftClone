#pragma once
#include "ShapeData.h"
class ShapeGenerator
{
public:
	static ShapeData<Vertex> makeTriangle();
	static ShapeData<VertexTex> makeSquare();
	static ShapeData<Vertex> makeCube();
	static ShapeData<VertexTex> makeTexturedCube();
};