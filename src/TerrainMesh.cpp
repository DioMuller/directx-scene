#include "TerrainMesh.h"

////////////////////////////////////
// Constructors
////////////////////////////////////
TerrainMesh::TerrainMesh(math::Vector3D position, std::string shaderTechnique, std::string heightmap, float heightScale, float heightOffset, float width, float height, int columns, int rows, D3DCOLOR color, bool inverted, std::wstring texture)
	: PlaneMesh(position, shaderTechnique, width, height, columns, rows, color, texture)
{
	this->inverted = inverted;
	this->heightmap.loadRAW(columns, rows, heightmap.c_str(), heightScale, heightOffset);
}


TerrainMesh::~TerrainMesh()
{
}

////////////////////////////////////
// Methods
////////////////////////////////////
void TerrainMesh::GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z)
{
	float scale = 0.001f;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			vertexes.push_back({ D3DXVECTOR3(initial_x + (i * diff_x), (inverted ? -1 : 1) * heightmap(i, j), initial_z + (j * diff_z)), color, D3DXVECTOR2((float)i, (float) j) * scale });
		}
	}
}