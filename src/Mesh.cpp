#include "Mesh.h"
#include "mage/HandleError.h"

Mesh::Mesh(math::Vector3D position, std::string shaderTechnique, std::wstring textureFile)
{
	this->position = position;
	this->rotation = math::Vector3D(0.0f, 0.0f, 0.0f);
	this->shaderTechnique = shaderTechnique;
	this->textureFile = textureFile;
}

Mesh::Mesh(math::Vector3D position, std::string shaderTechnique)
{
	this->position = position;
	this->rotation = math::Vector3D(0.0f, 0.0f, 0.0f);
	this->shaderTechnique = shaderTechnique;
	this->textureFile = L"";
}

Mesh::~Mesh()
{
	vertexBuffer->Release();
	indexBuffer->Release();
	if( texture != nullptr ) texture->Release();
}

void Mesh::Initialize(IDirect3DDevice9* device)
{
	GenerateMesh();

	// Create vertex buffer on the device.
	vertexBuffer = Vertex::createVertexBuffer(device, vertexes);

	// Create index buffer on the device.
	HR(device->CreateIndexBuffer(sizeof(WORD)* indexCount, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, nullptr));

	// Creates texture, if it exists.
	if (textureFile != L"")
	{
		HR(D3DXCreateTextureFromFile(device, textureFile.c_str(), &texture));
	}
	else
	{
		texture = nullptr;
	}

	// Writes indexes on the video memory.
	WORD* pWord;
	HR(indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pWord), 0));
	for (int i = 0; i < indexCount; i++)
		pWord[i] = static_cast<WORD>(indexes[i]);
	HR(indexBuffer->Unlock());
}

void Mesh::Render(IDirect3DDevice9* device, ID3DXEffect* shader, int maxPasses)
{
	// Get technique
	D3DXHANDLE tech = shader->GetTechniqueByName(shaderTechnique.c_str());
	HR(shader->SetTechnique(tech));

	// World Transform
	D3DXMATRIX world;

	D3DXMatrixIdentity(&world);
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);

	D3DXMATRIX rotation_x, rotation_y, rotation_z;
	D3DXMatrixIdentity(&rotation_x);
	D3DXMatrixIdentity(&rotation_y);
	D3DXMatrixIdentity(&rotation_z);

	D3DXMatrixRotationX(&rotation_x, this->rotation.x);
	D3DXMatrixRotationY(&rotation_y, this->rotation.y);
	D3DXMatrixRotationZ(&rotation_z, this->rotation.z);

	D3DXMATRIX rotation = rotation_x * rotation_y * rotation_z;

	world = rotation * world;

	D3DXHANDLE hWorld = shader->GetParameterByName(0, "World");
	HR(shader->SetMatrix(hWorld, &world));

	if (texture != nullptr)
	{
		D3DXHANDLE hTexture = shader->GetParameterByName(0, "Texture");
		HR(shader->SetTexture(hTexture, texture));
	}

	UINT passes = 0;
	HR(shader->Begin(&passes, 0));
	for (UINT i = 0; i < passes; ++i)
	{
		HR(shader->BeginPass(i));

		// Set vertex declaration
		HR(device->SetVertexDeclaration(Vertex::getDeclaration(device)));

		// Sets stream source
		HR(device->SetStreamSource(
			0, // Stream number 
			vertexBuffer, // Data 
			0, // Offset 
			sizeof(Vertex))); // Vertex data size

		// Set indexes
		HR(device->SetIndices(indexBuffer));

		// Draw Primitives
		HR(device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount));	
		HR(shader->EndPass());
	}

	HR(shader->End());

	// Reset world position
	hWorld = shader->GetParameterByName(0, "World");
	D3DXMatrixIdentity(&world);
	HR(shader->SetMatrix(hWorld, &world));
}

void Mesh::GenerateMesh()
{

}