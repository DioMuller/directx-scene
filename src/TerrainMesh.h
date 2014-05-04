#pragma once
#include "PlaneMesh.h"
#include "Heightmap.h"

class TerrainMesh : public PlaneMesh
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		Heightmap heightmap;
		bool inverted;
	////////////////////////////////////
	// Constructors
	////////////////////////////////////
	public:
		TerrainMesh(math::Vector3D position, std::string shaderTechnique, std::string Heightmap, float heightScale, float heightOffset, float width, float height, int columns, int rows, D3DCOLOR color, bool inverted, std::wstring texture);
		~TerrainMesh();

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		void GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z);
};

