#pragma once

#include "mage/AbstractGameLoop.h"
#include "mage/Effect.h"
#include <d3dx9.h>

//Passo A1 - Definição do formato do vértice (ver .h)

struct MyVertex
{
	D3DXVECTOR3 position;   // Posição
    DWORD color;			// Cor
};

class RotatingTriangle : public mage::AbstractGameLoop
{			
	private:		
		IDirect3DVertexDeclaration9* vertexDeclaration;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		mage::Effect shader;
		float angle;
	public:
		RotatingTriangle();
		virtual void setup(IDirect3DDevice9* device);
		virtual bool process(float time);
		virtual void paint(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& evt);
};