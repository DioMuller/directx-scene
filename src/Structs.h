#pragma once
#include <d3dx9.h>
#include <vector>

struct Vertex
{
	D3DXVECTOR3 position;   // Position
	DWORD color;			// Color
};

struct Mesh
{	
	std::vector<Vertex> vertices;
	std::vector<DWORD> indexes;
	int verticeCount;
};