#include "CubeMesh.h"
#include "mage/HandleError.h"


CubeMesh::CubeMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, float depth, std::wstring texture) : Mesh(position, shaderTechnique, texture)
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
	vertexes.push_back({ D3DXVECTOR3(-norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,1) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) });
	vertexes.push_back({ D3DXVECTOR3(-norm_x, norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(1,0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(1,1) });

	vertexes.push_back({ D3DXVECTOR3(-norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(1,1) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,1) });
	vertexes.push_back({ D3DXVECTOR3(-norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) });
	vertexes.push_back({ D3DXVECTOR3(norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(1,0) });

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

	// Bottom
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(0);
	indexes.push_back(0);
	indexes.push_back(5);
	indexes.push_back(1);

	// Top
	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(3);
	indexes.push_back(7);

	indexCount = indexes.size();

}

void CubeMesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	D3DXVECTOR4 pos = D3DXVECTOR4(position.x, position.y, position.z, 0);
	D3DXHANDLE hPosition = shader->GetParameterByName(0, "MeshPosition");
	HR(shader->SetVector(hPosition, &pos));
	Mesh::Render(device, shader, maxPasses);
}