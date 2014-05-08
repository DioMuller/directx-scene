#include "RaftMesh.h"
#include "mage/HandleError.h"

RaftMesh::RaftMesh(math::Vector3D position, std::string shaderTechnique, float width, float height, float depth) : Mesh(position, shaderTechnique)
{
	this->width = width;
	this->height = height;
	this->depth = depth;

	body = new CubeMesh(position, "TexturedTech", width, 0.1f * height, depth, L"assets/boards.png");
	mast = new CubeMesh(position, "TexturedTech", width * 0.1f, height, depth * 0.1f, L"assets/boards.png");
	mast->position.addY(height / 2.0f);

	characterPosition = math::Vector3D(width / 3.0f, 0.3f * height, depth / 3.0f);
	character = new Billboard(position + characterPosition, "CharacterTech", width / 8.0f , height/2.0f, L"assets/character.png");
}


RaftMesh::~RaftMesh()
{
	delete body;
	delete mast;
}

void RaftMesh::Initialize(IDirect3DDevice9* device)
{
	Mesh::Initialize(device);

	body->Initialize(device);
	mast->Initialize(device);
	character->Initialize(device);
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

	// Indexes (Sail)
	//    13  14
	// 15   16
	//
	// 17  18
	//    19   20
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(1);
	indexes.push_back(3);

	indexes.push_back(2);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(4);
	indexes.push_back(3);
	indexes.push_back(5);

	indexes.push_back(4);
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(6);
	indexes.push_back(5);
	indexes.push_back(7);

	indexCount = indexes.size();
	triangleCount = indexCount / 3;
	vertexCount = vertexes.size();

}

void RaftMesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	// TODO: Add Update() method for that?
	body->position = position;
	body->rotation = rotation;

	mast->position.x = position.x;
	mast->position.z = position.z;
	mast->rotation = rotation;

	math::Vector3D rotated = math::Vector3D(position).normalize() * characterPosition;
	rotated.y = characterPosition.y;
	character->position = position + rotated;
	//character->rotation = rotation;
	// END

	body->Render(device, shader, maxPasses);
	mast->Render(device, shader, maxPasses);
	character->Render(device, shader, maxPasses);

	D3DXVECTOR4 pos = D3DXVECTOR4(position.x, position.y, position.z, 0);
	D3DXHANDLE hPosition = shader->GetParameterByName(0, "MeshPosition");
	HR(shader->SetVector(hPosition, &pos));
	Mesh::Render(device, shader, maxPasses);
}