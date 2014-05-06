#include "RaftMesh.h"
#include "mage/HandleError.h"

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

	float sail_x = (width / 4);
	float sail_y = height;
	float sail_z = mast_z;

	float height_dist = height/8.0f;

	// Create vertexes (Mast)
	//    5   6
	// 1   2
	//    7   8
	// 3   4
	vertexes.push_back(Vertex(D3DXVECTOR3(-mast_x, 0.0f, mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(mast_x, 0.0f, mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-mast_x, mast_y, mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(mast_x, mast_y, mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-mast_x, 0.0f, -mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(mast_x, 0.0f, -mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-mast_x, mast_y, -mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(mast_x, mast_y, -mast_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));

	// Create vertexes (Body)
	//    11  12
	// 9   10
	vertexes.push_back(Vertex(D3DXVECTOR3(-body_x, body_y, -body_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(body_x, body_y, -body_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-body_x, body_y, body_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(body_x, body_y, body_z), D3DCOLOR_XRGB(49, 8, 18) , D3DXVECTOR2(0,0) ));

	// Create vertexes (Sail)
	//    13  14
	// 15   16
	//
	// 17  18
	//    19   20
	vertexes.push_back(Vertex(D3DXVECTOR3(-sail_x, sail_y, sail_z), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(sail_x, sail_y, sail_z), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-sail_x, sail_y - height_dist, sail_z - height_dist), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(sail_x, sail_y - height_dist, sail_z - height_dist), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-sail_x, sail_y - 5 * height_dist, sail_z - height_dist), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(sail_x, sail_y - 5 *height_dist, sail_z - height_dist), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(-sail_x, sail_y - 6 * height_dist, sail_z), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));
	vertexes.push_back(Vertex(D3DXVECTOR3(sail_x, sail_y - 6 * height_dist, sail_z), D3DCOLOR_XRGB(128, 128, 128) , D3DXVECTOR2(0,0) ));

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

	// Indexes (Sail)
	//    13  14
	// 15   16
	//
	// 17  18
	//    19   20
	indexes.push_back(12);
	indexes.push_back(13);
	indexes.push_back(14);
	indexes.push_back(14);
	indexes.push_back(13);
	indexes.push_back(15);

	indexes.push_back(14);
	indexes.push_back(15);
	indexes.push_back(16);
	indexes.push_back(16);
	indexes.push_back(15);
	indexes.push_back(17);

	indexes.push_back(16);
	indexes.push_back(17);
	indexes.push_back(18);
	indexes.push_back(18);
	indexes.push_back(17);
	indexes.push_back(19);

	indexCount = indexes.size();
	triangleCount = indexCount / 3;
	vertexCount = vertexes.size();

}

void RaftMesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	D3DXVECTOR4 pos = D3DXVECTOR4(position.x, position.y, position.z, 0);
	D3DXHANDLE hPosition = shader->GetParameterByName(0, "MeshPosition");
	HR(shader->SetVector(hPosition, &pos));
	Mesh::Render(device, shader, maxPasses);
}