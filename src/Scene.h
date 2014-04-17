#pragma once
#include "mage/AbstractGameLoop.h"
#include "mage/Effect.h"
#include "Mesh.h"
#include "PlaneMesh.h"
#include "CubeMesh.h"

class Scene : public mage::AbstractGameLoop
{
	private:
		// Shader
		ID3DXEffect* shader;
		PlaneMesh* plane;
		CubeMesh* cube;
		float time;

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
};

