#pragma once

#include "mage/AbstractGameLoop.h"
#include <d3dx9.h>
#include <vector>
#include "Vertex.h"

//Passo A1 - Definição do formato do vértice (ver .h)

class WaveGrid : public mage::AbstractGameLoop
{			
	private:
		float time;
		ID3DXEffect* shader;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 indexBuffer;

		int numIndices;
		int numTriangles;
		int numVertices;

	public:
		virtual void setup(IDirect3DDevice9* device);
		void createTriangleGrid(float w, float h, int rows, int cols, 
			std::vector<Vertex>& vertices, std::vector<DWORD>& indices, int& numTriangles);
		virtual bool process(float time);
		virtual void paint(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& evt);
};