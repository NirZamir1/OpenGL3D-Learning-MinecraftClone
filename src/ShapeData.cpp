#include "ShapeData.h"
#include <iostream>
ShapeData::ShapeData():vertecies(0),indecies(0),numIndecies(0),numVertecies(0)
{
}
ShapeData::ShapeData(const ShapeData& data)
{
	typedef unsigned short ushort;
	numVertecies = data.numVertecies;
	numIndecies = data.numIndecies;
	indecies = new ushort[numIndecies];
	vertecies = new Vertex[numVertecies];
	memcpy(indecies, data.indecies, numIndecies*sizeof(ushort));
	memcpy(vertecies, data.vertecies, numVertecies*sizeof(Vertex));
}

void ShapeData::CleanUp()
{
	if(vertecies != nullptr)
		delete[] vertecies;
	if(indecies != nullptr)
		delete[] indecies;
	numIndecies = 0;
	numVertecies = 0;
}

int ShapeData::GetVerteciesBufferSize()
{
	return sizeof(Vertex)*numVertecies;
}

int ShapeData::GetIndeciesBufferSize()
{
	return sizeof(unsigned short)*numIndecies;
}
