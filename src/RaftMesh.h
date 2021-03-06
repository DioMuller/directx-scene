#pragma once
#include "Mesh.h"
#include "CubeMesh.h"
#include "Billboard.h"

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
		Billboard* character;
		math::Vector3D characterPosition;

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

