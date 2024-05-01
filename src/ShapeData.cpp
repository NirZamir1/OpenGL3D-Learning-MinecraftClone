#include "ShapeData.h"
#include <iostream>
template <typename T>
ShapeData<T>::ShapeData():vertecies(0),indecies(0),numIndecies(0),numVertecies(0)
{
}
template <typename T>
ShapeData<T>::ShapeData(const ShapeData& data)
{
	std::cout << "copy Constructor" << std::endl;
	typedef unsigned short ushort;
	numVertecies = data.numVertecies;
	numIndecies = data.numIndecies;
	indecies = new ushort[numIndecies];
	vertecies = new T[numVertecies];
	memcpy(indecies, data.indecies, numIndecies*sizeof(ushort));
	memcpy(vertecies, data.vertecies, numVertecies*sizeof(T));
}
template <typename T>
void ShapeData<T>::CleanUp()
{
	if(vertecies != nullptr)
		delete[] vertecies;
	if(indecies != nullptr)
		delete[] indecies;
	numIndecies = 0;
	numVertecies = 0;
}

template <typename T>
int ShapeData<T>::GetVerteciesBufferSize()
{
	return sizeof(T)*numVertecies;
}

template <typename T>
int ShapeData<T>::GetIndeciesBufferSize()
{
	return sizeof(unsigned short)*numIndecies;
}

template struct ShapeData<Vertex>;  // Instantiate for Vertex type if needed
template struct ShapeData<VertexTex>;  // Instantiate for Vertex type if needed
