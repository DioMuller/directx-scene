#pragma once
#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

struct Mesh
{	
	std::vector<Vertex> vertexes;
	std::vector<DWORD> indexes;
	int vertexCount;
};