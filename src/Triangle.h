#pragma once

#include "mage/AbstractGameLoop.h"

//Passo A1 - Definição do formato do vértice (ver .h)

struct MyVertex
{
	FLOAT x, y, z, w;   // Posições x,y,z e w.
    DWORD color;		// Cor
};

class Triangle : public mage::AbstractGameLoop
{			
	private:		
		IDirect3DVertexDeclaration9* vertexDeclaration;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	public:
		virtual void setup(IDirect3DDevice9* device);
		virtual void paint(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& evt);
};