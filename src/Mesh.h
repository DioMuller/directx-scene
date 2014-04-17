#pragma once
#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

class Mesh
{	
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	protected:
		std::vector<Vertex> vertexes;
		std::vector<DWORD> indexes;
		int vertexCount;
		int indexCount;
		int triangleCount;
		bool initialized;

		IDirect3DVertexBuffer9* vertexBuffer;
		IDirect3DIndexBuffer9* indexBuffer;

	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		Mesh();
		~Mesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void Initialize(IDirect3DDevice9* device);
		virtual void GenerateMesh();
		void Render(IDirect3DDevice9* device);
};