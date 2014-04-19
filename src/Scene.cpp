#include "Scene.h"
#include "mage/WindowsEvent.h"
#include "mage/GameWindow.h"
#include "mage/HandleError.h"

using namespace mage;

Scene::Scene()
{

}

Scene::~Scene()
{
}

void Scene::setup(IDirect3DDevice9* device)
{
	running = true;
	time = 0.0f;

	// Create camera.
	camera = new Camera(60.0f, 1.0f, 100.0f, -20.0f, 5.0f);

	// Raft rotation extra value.
	rotationDiff = D3DXToRadian(-90);

	/* TEST */
	int cols = 256;
	int rows = 256;
	float width = 350.0f;
	float height = 350.0f;

	// Generate meshes.
	terrain = new TerrainMesh(math::Vector3D(0, 0, 0), "TerrainTech", "heightmap.raw", cols, height, cols, rows, D3DCOLOR_XRGB(0, 150, 0));
	terrain->Initialize(device);

	plane = new PlaneMesh(math::Vector3D(0, 0, 0), "WaveTech", width, height, cols, rows, D3DCOLOR_XRGB(0, 0, 150));
	plane->Initialize(device);
	
	raft = new RaftMesh(math::Vector3D(0, 0, 0), "TransformTech", 5.0f, 4.0f, 5.0f);
	raft->Initialize(device);

	// Shader
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(device, _T("SimpleShader.fx"), 0, 0, D3DXSHADER_DEBUG, 0, &shader, &errors));

	if (errors)
	{
		MessageBoxA(0, static_cast<char*>(errors->GetBufferPointer()), 0, 0);
		exit(1);
	}

	//No lightning
	HR(device->SetRenderState(D3DRS_LIGHTING, FALSE));

	// No Culling
	HR(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
}

void Scene::processEvent(const WindowsEvent& evt)
{
	switch (evt.type)
	{
		case WM_KEYDOWN:
			if( evt.wParam == VK_ESCAPE )
				running = false;
			return;
	}
}

bool Scene::process(float time)
{
	// Nothing else to do, for now.
	this->time += time;
	this->raft->position = math::Vector3D(0, 0, 1) * 10;
	this->raft->position.rotateY(this->time/4);
	this->raft->rotation.y = this->time / 4 + rotationDiff;
	return AbstractGameLoop::process(time);
}

void Scene::paint(IDirect3DDevice9* device)
{
    //Clear screen
	device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(101, 156, 239), 1.0f, 0);

    device->BeginScene();    // Begins Scene

	// Drawing code BEGIN

	//--------------------------------------------------
	// Camera
	//--------------------------------------------------
	camera->UpdateView(shader);

	//--------------------------------------------------
	// Rendering
	//--------------------------------------------------

	D3DXHANDLE hTime = shader->GetParameterByName(0, "Time");
	HR(shader->SetFloat(hTime, time));

	raft->Render(device, shader);
	terrain->Render(device, shader);
	plane->Render(device, shader);

    device->EndScene();    // Ends Scene

    device->Present(nullptr, nullptr, nullptr, nullptr);    // Show frame.
}

void Scene::onLostDevice()
{
}

void Scene::onRestoreDevice(IDirect3DDevice9* device)
{
}

void Scene::shutDown(IDirect3DDevice9* device)
{
	delete plane;
	delete raft;
	delete camera;
}