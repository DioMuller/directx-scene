#pragma once
#include <d3dx9.h>
#include <vector>
#include "Vertex.h"
#include "math/Vector3D.h"

class Mesh
{	
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	public:
		math::Vector3D position;
		math::Vector3D rotation;
	protected:
		std::vector<Vertex> vertexes;
		std::vector<DWORD> indexes;
		int vertexCount;
		int indexCount;
		int triangleCount;
		bool initialized;
		std::string shaderTechnique;
		std::wstring textureFile;

		IDirect3DVertexBuffer9* vertexBuffer;
		IDirect3DIndexBuffer9* indexBuffer;
		IDirect3DTexture9* texture;

	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		Mesh(math::Vector3D position, std::string shaderTechnique, std::wstring textureFile);
		Mesh(math::Vector3D position, std::string shaderTechnique);
		~Mesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		virtual void Initialize(IDirect3DDevice9* device);
		virtual void GenerateMesh();
		virtual void Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses = INT_MAX);
};