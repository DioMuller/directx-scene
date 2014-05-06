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
	camera = new Camera(60.0f, 1.0f, 800.0f, -20.0f, 5.0f);
	cameraRotation = 0;
	cameraHeight = 0;

	// Raft rotation extra value.
	rotationDiff = D3DXToRadian(-90);

	/* TEST */
	int cols = 128;
	int rows = 128;
	float width = 600.0f;
	float height = 600.0f;

	// Generate meshes.
	terrain = new TerrainMesh(math::Vector3D(0, 0, 0), "TerrainTech", "assets/samplehheightmap_01.raw", 1.0f, -87.0f, width, height, 129, 129, D3DCOLOR_XRGB(150, 150, 0), true, L"assets/grass.png");
	terrain->Initialize(device);

	plane = new PlaneMesh(math::Vector3D(0, 0, 0), "WaveTech", width, height, cols, rows, D3DCOLOR_XRGB(0, 0, 120), L"");
	plane->Initialize(device);
	
	raft = new RaftMesh(math::Vector3D(0, 0, 10), "TransformTech", 5.0f, 4.0f, 5.0f);
	raft->Initialize(device);

	boxes.push_back(new CubeMesh(math::Vector3D(0, 0, 0), "TexturedTech", 1, 1, 1, L"assets/crate.png"));
	boxes.push_back(new CubeMesh(math::Vector3D(15, 0, -15), "TexturedTech", 1, 1, 1, L"assets/crate.png"));
	boxes.push_back(new CubeMesh(math::Vector3D(25, 0, 5), "TexturedTech", 1, 1, 1, L"assets/crate.png"));
	boxes.push_back(new CubeMesh(math::Vector3D(-35, 0, 5), "TexturedTech", 1, 1, 1, L"assets/crate.png"));

	for (CubeMesh* mesh : boxes)
	{
		mesh->Initialize(device);
	}

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
		if (evt.wParam == VK_ESCAPE)
			running = false;
		if (evt.wParam == VK_RIGHT)
			cameraRotation += 1;
		if (evt.wParam == VK_LEFT)
			cameraRotation -= 1;
		if (evt.wParam == VK_UP)
			cameraHeight = 1;
		if (evt.wParam == VK_DOWN)
			cameraHeight = -1;
		break;
	case WM_KEYUP:
		if (evt.wParam == VK_RIGHT)
			cameraRotation -= 1;
		if (evt.wParam == VK_LEFT)
			cameraRotation += 1;
		if (evt.wParam == VK_UP)
			cameraHeight = 0;
		if (evt.wParam == VK_DOWN)
			cameraHeight = 0;
		break;
		
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
	if (cameraRotation != 0) camera->Rotate(D3DXToRadian(cameraRotation));
	if (cameraHeight != 0) camera->AddHeight(0.03f * (float)cameraHeight);

	//--------------------------------------------------
	// Rendering
	//--------------------------------------------------

	D3DXHANDLE hTime = shader->GetParameterByName(0, "Time");
	HR(shader->SetFloat(hTime, time));

	raft->Render(device, shader);
	terrain->Render(device, shader);

	for (CubeMesh* mesh : boxes)
	{
		mesh->Render(device, shader);
	}

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