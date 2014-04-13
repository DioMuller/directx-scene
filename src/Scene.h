#pragma once
#include "mage/AbstractGameLoop.h"
#include "mage/Effect.h"
#include <d3dx9.h>

struct MyVertex
{
	D3DXVECTOR3 position;   // Posição
	DWORD color;			// Cor
};

class Scene : public mage::AbstractGameLoop
{
	private:
		bool running;
		IDirect3DVertexBuffer9* vertexBuffer;
		IDirect3DVertexDeclaration9* vertexDeclaration;
		MyVertex *vertices;
		mage::Effect shader;
		int numvertexes;
		float angle;
	public:
		Scene(void);
		~Scene(void);

		virtual void setup(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& msg);
		virtual bool process(float time);
		virtual void paint(IDirect3DDevice9* device);
		virtual void onLostDevice();
		virtual void onRestoreDevice(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);
};

