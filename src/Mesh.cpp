#include "Mesh.h"
#include "mage/HandleError.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	vertexBuffer->Release();
	indexBuffer->Release();
}

void Mesh::Initialize(IDirect3DDevice9* device)
{
	GenerateMesh();

	// Create vertex buffer on the device.
	vertexBuffer = Vertex::createVertexBuffer(device, vertexes);

	// Create index buffer on the device.
	HR(device->CreateIndexBuffer(sizeof(WORD)* indexCount, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, nullptr));

	// Writes indexes on the video memory.
	WORD* pWord;
	HR(indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pWord), 0));
	for (int i = 0; i < indexCount; i++)
		pWord[i] = static_cast<WORD>(indexes[i]);
	HR(indexBuffer->Unlock());
}

void Mesh::Render(IDirect3DDevice9* device)
{
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
}

void Mesh::GenerateMesh()
{

}