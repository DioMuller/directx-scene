#pragma once
#include "PlaneMesh.h"
#include "Heightmap.h"
#include "Billboard.h"

class TerrainMesh : public PlaneMesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		Heightmap heightmap;
		std::wstring treeFilename;
		std::vector<Billboard*> decorations;
		int treeCount;
		bool inverted;
	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		TerrainMesh(math::Vector3D position, std::string shaderTechnique, std::string Heightmap, float heightScale, float heightOffset, float width, float height, int columns, int rows, D3DCOLOR color, bool inverted, std::wstring texture, std::wstring treeTexture, int treeCount);
		~TerrainMesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z);
		void Initialize(IDirect3DDevice9* device);
		void Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses = INT_MAX);
};

