#include "RaftMesh.h"


RaftMesh::RaftMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, float depth) : Mesh(position, shaderTechnique)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}


RaftMesh::~RaftMesh()
{
}

void RaftMesh::GenerateMesh()
{
	// Initial position where the mesh will be drawn. 
	float mast_x = (width / 32);
	float mast_y = height;
	float mast_z = (depth / 32);

	float body_x = (width / 2);
	float body_y = 0.0f;
	float body_z = (depth / 2);

	// Vertex count (8 mast, 4 body)
	vertexCount = 12;

	// Triangle count (10 mast, 2 body)
	triangleCount = 12;

	// Create vertexes (Mast)
	//    5   6
	// 1   2
	//    7   8
	// 3   4
	vertexes.push_back({ D3DXVECTOR3(-mast_x, 0.0f, mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(mast_x, 0.0f, mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(-mast_x, mast_y, mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(mast_x, mast_y, mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(-mast_x, 0.0f, -mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(mast_x, 0.0f, -mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(-mast_x, mast_y, -mast_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(mast_x, mast_y, -mast_z), D3DCOLOR_XRGB(49, 8, 18) });

	// Create vertexes (Body)
	//    11  12
	// 9   10
	vertexes.push_back({ D3DXVECTOR3(-body_x, body_y, -body_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(body_x, body_y, -body_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(-body_x, body_y, body_z), D3DCOLOR_XRGB(49, 8, 18) });
	vertexes.push_back({ D3DXVECTOR3(body_x, body_y, body_z), D3DCOLOR_XRGB(49, 8, 18) });

	// Create indexes (Mast)
	// Front
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(1);
	indexes.push_back(3);

	// Right
	indexes.push_back(1);
	indexes.push_back(5);
	indexes.push_back(3);
	indexes.push_back(3);
	indexes.push_back(5);
	indexes.push_back(7);

	// Back
	indexes.push_back(5);
	indexes.push_back(4);
	indexes.push_back(7);
	indexes.push_back(7);
	indexes.push_back(4);
	indexes.push_back(6);

	// Left
	indexes.push_back(4);
	indexes.push_back(0);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(0);
	indexes.push_back(2);

	// Top
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(3);
	indexes.push_back(7);

	// Indexes (Body)
	//    11  12
	// 9   10
	indexes.push_back(10);
	indexes.push_back(11);
	indexes.push_back(8);
	indexes.push_back(8);
	indexes.push_back(11);
	indexes.push_back(9);

	indexCount = indexes.size();

}