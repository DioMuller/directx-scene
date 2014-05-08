#include "TerrainMesh.h"

////////////////////////////////////
// Constructors
////////////////////////////////////
TerrainMesh::TerrainMesh(math::Vector3D position, std::string shaderTechnique, std::string heightmap, float heightScale, float heightOffset, float width, float height, int columns, int rows, D3DCOLOR color, bool inverted, std::wstring texture, std::wstring treeTexture, int treeCount)
	: PlaneMesh(position, shaderTechnique, width, height, columns, rows, color, texture)
{
	this->inverted = inverted;
	this->heightmap.loadRAW(columns, rows, heightmap.c_str(), heightScale, heightOffset);
	this->treeCount = treeCount;
	this->treeFilename = treeTexture;
}


TerrainMesh::~TerrainMesh()
{
	while (decorations.size() != 0)
	{
		Billboard* elem = decorations[decorations.size() - 1];
		decorations.pop_back();
		delete elem;
	}
}

////////////////////////////////////
// Methods
////////////////////////////////////
void TerrainMesh::GenerateVertexes(float initial_x, float diff_x, float initial_z, float diff_z)
{
	float scale = 0.1f;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			vertexes.push_back(Vertex(D3DXVECTOR3(initial_x + (i * diff_x), (inverted ? -1 : 1) * heightmap(i, j), initial_z + (j * diff_z)), color, D3DXVECTOR2((float)i, (float) j) * scale ));
		}
	}

	// Let's use the parameters to initialize the decorations too!
	int trees = 0;
	while (trees < treeCount)
	{
		int i = rand() % columns;
		int j = rand() % rows;
		float treeHeight = (float) this->heightmap(i, j) - 2.5f;

		if (treeHeight < -2.0f)
		{
			math::Vector3D pos = math::Vector3D(initial_x + (i * diff_x), (inverted ? -1 : 1) * treeHeight, initial_z + (j * diff_z));

			decorations.push_back(new Billboard(pos, "BillboardTech", 8, 8, treeFilename));
			trees++;
		}
	}
}

void TerrainMesh::Initialize(IDirect3DDevice9* device)
{
	PlaneMesh::Initialize(device);

	for (Billboard* item : decorations)
	{
		item->Initialize(device);
	}
}

void TerrainMesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	for (Billboard* item : decorations)
	{
		item->Render(device,shader, maxPasses);
	}

	PlaneMesh::Render(device, shader, maxPasses);
}