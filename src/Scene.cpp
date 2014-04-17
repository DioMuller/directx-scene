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

	/* TEST */
	int cols = 50;
	int rows = 50;
	float width = 10.0f;
	float height = 10.0f;

	time = 0.0f;

	// Generate Plane mesh vertexes and indexes.
	plane = new PlaneMesh(width, height, cols, rows);
	plane->Initialize(device);

	cube = new CubeMesh(2.0f, 2.0f, 2.0f);
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
	// World transform
	//--------------------------------------------------

	// Translation Matrix
	D3DXMATRIX world;

	D3DXMatrixIdentity(&world);
	//D3DXMatrixTranslation(&world, 0, 0, 0);

	D3DXMATRIX rotation;
	D3DXMatrixIdentity(&rotation);
	//D3DXMatrixRotationY(&rotation, D3DXToRadian(180));

	world = rotation * world;

	//--------------------------------------------------
	// View transform
	//--------------------------------------------------
	D3DXMATRIX view;
	//D3DXMatrixIdentity(&view);	
	D3DXMatrixLookAtLH(&view,
		&D3DXVECTOR3(0.0f, 5.0f, 10.0f), // posição da câmera
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),  // local para onde olha
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)); // topo do mundo

	//--------------------------------------------------
	// Projection transform
	//--------------------------------------------------
	D3DXMATRIX projection;     // the projection transform matrix
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DXToRadian(60),					 // Vertical FOV
		mage::GameWindow::get().getAspect(), // aspect ratio
		1.0f,								 // Near
		100.0f);							 // Far

	//--------------------------------------------------
	// Shader
	//--------------------------------------------------
	
	// Parameter definition
	D3DXHANDLE hWorld = shader->GetParameterByName(0, "World");
	HR(shader->SetMatrix(hWorld, &world));

	D3DXHANDLE hView = shader->GetParameterByName(0, "View");
	HR(shader->SetMatrix(hView, &view));

	D3DXHANDLE hProjection = shader->GetParameterByName(0, "Projection");
	HR(shader->SetMatrix(hProjection, &projection));

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
		cube->Render(device);
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
		plane->Render(device);
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
}