#pragma once
#include "ShapeData.h"
class ShapeGenerator
{
public:
	static ShapeData<Vertex> makeTriangle();
	static ShapeData<Vertex2> makeSquare();
	static ShapeData<Vertex> makeCube();
};