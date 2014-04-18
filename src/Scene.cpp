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
	camera = new Camera(60.0f, 1.0f, 100.0f, 10.0f, 5.0f);

	/* TEST */
	int cols = 100;
	int rows = 100;
	float width = 150.0f;
	float height = 150.0f;

	// Generate Plane mesh vertexes and indexes.
	plane = new PlaneMesh(math::Vector3D(0,0,0), width, height, cols, rows);
	plane->Initialize(device);

	cube = new CubeMesh(math::Vector3D(0,0,0), 2.0f, 2.0f, 2.0f);
	cube->Initialize(device);

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
	return AbstractGameLoop::process(time);
}

void Scene::paint(IDirect3DDevice9* device)
{
    //Clear screen
	device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 20, 80), 1.0f, 0);

    device->BeginScene();    // Begins Scene

	// Drawing code BEGIN

	//--------------------------------------------------
	// Camera
	//--------------------------------------------------
	camera->UpdateView(shader);

	//--------------------------------------------------
	// Shader
	//--------------------------------------------------

	D3DXHANDLE hTime = shader->GetParameterByName(0, "Time");
	HR(shader->SetFloat(hTime, time));

	// Get technique
	D3DXHANDLE tech = shader->GetTechniqueByName("TransformTech");
	HR(shader->SetTechnique(tech));

	// Passes
	UINT passes = 0;
	HR(shader->Begin(&passes, 0));
	for (UINT i = 0; i < passes; ++i)
	{
		HR(shader->BeginPass(i));
		cube->Render(device, shader);
		HR(shader->EndPass());
	}
	HR(shader->End());

	// Get technique
	tech = shader->GetTechniqueByName("WaveTech");
	HR(shader->SetTechnique(tech));

	// Passes
	passes = 0;
	HR(shader->Begin(&passes, 0));
	for (UINT i = 0; i < passes; ++i)
	{
		HR(shader->BeginPass(i));
		plane->Render(device, shader);
		HR(shader->EndPass());
	}
	HR(shader->End());

	// Drawing Code END

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
	delete cube;
	delete camera;
}