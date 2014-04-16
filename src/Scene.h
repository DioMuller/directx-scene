#pragma once
#include "mage/AbstractGameLoop.h"
#include "mage/Effect.h"
#include "Structs.h"

class Scene : public mage::AbstractGameLoop
{
	private:
		// Vertex Buffer
		IDirect3DVertexBuffer9* vertexBuffer;
		// Index Buffer
		IDirect3DIndexBuffer9* indexBuffer;
		// Shader
		ID3DXEffect* shader;
		// Number of Vertexes
		int vertexCount;
		// Number of triangles
		int triangleCount;

		// Cilinder
		ID3DXMesh* cilinder;
	public:
		Scene(void);
		~Scene(void);

		// Game Loop Methods
		virtual void setup(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& msg);
		virtual bool process(float time);
		virtual void paint(IDirect3DDevice9* device);
		virtual void onLostDevice();
		virtual void onRestoreDevice(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);

		// Geometry Methods
		Mesh createPlaneMesh(float width, float height, int columns, int rows);
};

