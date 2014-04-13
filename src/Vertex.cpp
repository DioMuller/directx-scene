#include "Vertex.h"
#include "mage/HandleError.h"

IDirect3DVertexDeclaration9* Vertex::declaration = nullptr;

using namespace std;

Vertex::Vertex() : position(), color()
{
}

Vertex::Vertex(const D3DXVECTOR3& _position, const D3DCOLOR& _color)
	: position(_position), color(_color)
{
}

Vertex::Vertex(const D3DXVECTOR3& _position, float r, float g, float b, float a)
	: position(_position), color(D3DCOLOR_COLORVALUE(r, g, b, a))
{
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a)
	: position(x, y, z), color(D3DCOLOR_COLORVALUE(r, g, b, a))
{
}


IDirect3DVertexDeclaration9* Vertex::getDeclaration(IDirect3DDevice9* device)
{	
	if (declaration)
		return declaration;

	D3DVERTEXELEMENT9 decl[] = 
	{
	   {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0,  12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	   D3DDECL_END()
	};
	
	HR(device->CreateVertexDeclaration(decl, &declaration));
	return declaration;
}

void Vertex::releaseDeclaration()
{
	declaration->Release();
	declaration = nullptr;
}

IDirect3DVertexBuffer9* Vertex::createVertexBuffer(IDirect3DDevice9* device, const std::vector<Vertex>& vertices, D3DPOOL pool, DWORD usage, HANDLE* pSharedHandle)
{
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	HR(device->CreateVertexBuffer(
		sizeof(Vertex) * vertices.size(), usage, 0, pool,
		&vertexBuffer, pSharedHandle));

	Vertex* v = 0;
	HR(vertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&v), 0));
	for (unsigned i = 0; i < vertices.size(); ++i)
		v[i] = vertices[i];
	HR(vertexBuffer->Unlock());

	return vertexBuffer;
}
