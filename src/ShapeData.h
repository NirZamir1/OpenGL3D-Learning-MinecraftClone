#pragma once
#include "VertexStruct.h"
template <typename T>
struct ShapeData 
{
	ShapeData();
	ShapeData(const ShapeData& data);
	void CleanUp();
	int GetVerteciesBufferSize();
	int GetIndeciesBufferSize();
	T* vertecies;
	unsigned int numVertecies;
	unsigned short* indecies;
	unsigned int numIndecies;
};
