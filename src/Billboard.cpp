#include "Billboard.h"
#include "mage/HandleError.h"


Billboard::Billboard(math::Vector3D position, std::string shaderTechnique, float width, float height, std::wstring texture) : Mesh(position, shaderTechnique, texture)
{
	this->width = width;
	this->height = height;
}


Billboard::~Billboard()
{
}

void Billboard::GenerateMesh()
{
	// Initial position where the mesh will be drawn. 
	float norm_x = (width / 2);
	float norm_y = (height / 2);

	// Front Face
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, -norm_y, 0.0f), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2(0.0f, 1.0f)));
	vertexes.push_back(Vertex(D3DXVECTOR3(-norm_x, norm_y, 0.0f), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2(0.0f, 0.0f)));
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x, norm_y, 0.0f), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2(1.0f, 0.0f)));
	vertexes.push_back(Vertex(D3DXVECTOR3(norm_x, -norm_y, 0.0f), D3DCOLOR_XRGB(49, 8, 18), D3DXVECTOR2(1.0f, 1.0f)));

	// Create indexes

	// Front
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(0);
	indexes.push_back(2);
	indexes.push_back(3);

	indexCount = indexes.size();
	triangleCount = indexes.size() / 3;
	vertexCount = vertexes.size();
}