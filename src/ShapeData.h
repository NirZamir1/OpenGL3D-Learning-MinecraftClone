#pragma once
#include "VertexStruct.h"
template<typename t>
struct ShapeData 
{
	ShapeData();
	ShapeData(const ShapeData& data);
	void CleanUp();
	int GetVerteciesBufferSize();
	int GetIndeciesBufferSize();
	t* vertecies;
	unsigned int numVertecies;
	unsigned short* indecies;
	unsigned int numIndecies;
};