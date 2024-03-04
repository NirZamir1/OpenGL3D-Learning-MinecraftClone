#pragma once
#include "VertexStruct.h"
struct ShapeData 
{
	ShapeData();
	ShapeData(const ShapeData& data);
	void CleanUp();
	int GetVerteciesBufferSize();
	int GetIndeciesBufferSize();
	Vertex* vertecies;
	unsigned int numVertecies;
	unsigned short* indecies;
	unsigned int numIndecies;
};