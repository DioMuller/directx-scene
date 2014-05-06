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

	// Front Face
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x,  norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x,  norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));

	// Back Face
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, -norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x,  norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x,  norm_y, norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));

	// Top
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));

	// Bottom
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3( norm_x, -norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));

	//Left
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x,  norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x,  norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));

	//Right
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x, -norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 1.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x,  norm_y, -norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 0.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x,  norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 0.0f) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x, -norm_y,  norm_z), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2( 1.0f, 1.0f) ));

	// Create indexes

	// Front
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(0);
	indexes.push_back(2);
	indexes.push_back(3);

	// Back
	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(4);
	indexes.push_back(6);
	indexes.push_back(7);

	// Top
	indexes.push_back(8);
	indexes.push_back(9);
	indexes.push_back(10);
	indexes.push_back(8);
	indexes.push_back(10);
	indexes.push_back(11);

	// Bottom
	indexes.push_back(12);
	indexes.push_back(13);
	indexes.push_back(14);
	indexes.push_back(12);
	indexes.push_back(14);
	indexes.push_back(15);

	// Left
	indexes.push_back(16);
	indexes.push_back(17);
	indexes.push_back(18);
	indexes.push_back(16);
	indexes.push_back(18);
	indexes.push_back(19);

	// Top
	indexes.push_back(20);
	indexes.push_back(21);
	indexes.push_back(22);
	indexes.push_back(20);
	indexes.push_back(22);
	indexes.push_back(23);

	indexCount = indexes.size();
	triangleCount = indexes.size() / 3;
	vertexCount = vertexes.size();

}

void CubeMesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	D3DXVECTOR4 pos = D3DXVECTOR4(position.x, position.y, position.z, 0);
	D3DXHANDLE hPosition = shader->GetParameterByName(0, "MeshPosition");
	HR(shader->SetVector(hPosition, &pos));
	Mesh::Render(device, shader, maxPasses);
}