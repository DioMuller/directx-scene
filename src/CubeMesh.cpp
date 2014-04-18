#include "CubeMesh.h"


CubeMesh::CubeMesh(math::Vector3D position, float width, float height, float depth) : Mesh(position)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
}


CubeMesh::~CubeMesh()
{
}

void CubeMesh::GenerateMesh()
{
	// Initial position where the mesh will be drawn. 
	float norm_x = (width / 2);
	float norm_y = (height / 2);
	float norm_z = (depth / 2);

	// Vertex count
	vertexCount = 8;

	// Triangle count
	triangleCount = 12;

	// Create vertexes
	//    5   6
	// 1   2
	//    7   8
	// 3   4
	vertexes.push_back({ D3DXVECTOR3(-norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(-norm_x, norm_y, norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, norm_y, norm_z), D3DCOLOR_XRGB(128, 0, 0) });

	vertexes.push_back({ D3DXVECTOR3(-norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(-norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(128, 0, 0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(128, 0, 0) });

	// Create indexes

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
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(0);
	indexes.push_back(0);
	indexes.push_back(5);
	indexes.push_back(1);

	// Bottom
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(3);
	indexes.push_back(7);

	indexCount = indexes.size();

}