#pragma once
#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

class Mesh
{	
	public:
		std::vector<Vertex> vertexes;
		std::vector<DWORD> indexes;
		int vertexCount;
		int indexCount;
		int triangleCount;
};