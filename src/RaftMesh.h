#pragma once
#include "Mesh.h"
#include "CubeMesh.h"

class RaftMesh : public Mesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		float width;
		float height;
		float depth;
		CubeMesh* mast;
		CubeMesh* body;

	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		RaftMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, float depth);
		~RaftMesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void Initialize(IDirect3DDevice9* device);
		void GenerateMesh();
		void Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses = INT_MAX);
};

