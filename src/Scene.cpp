#include "Scene.h"
#include "mage/WindowsEvent.h"
#include "mage/GameWindow.h"
#include "mage/HandleError.h"

using namespace mage;

Scene::Scene() : shader(_T("SimpleShader.fx"))
{
}

Scene::~Scene()
{
}

void Scene::setup(IDirect3DDevice9* device)
{
	running = true;

	angle = 0;

	// Declares Vertex format
	D3DVERTEXELEMENT9 decl[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};
	// Creates Vertex declaration
	vertexDeclaration = nullptr;
	HR(device->CreateVertexDeclaration(
		decl, &vertexDeclaration));

	// Creates mesh
	MyVertex vertices[] =
	{
		{ D3DXVECTOR3(3.0f, -3.0f, 0.0f), D3DCOLOR_XRGB(0, 0, 255) },
		{ D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DCOLOR_XRGB(0, 255, 0) },
		{ D3DXVECTOR3(-3.0f, -3.0f, 0.0f), D3DCOLOR_XRGB(255, 0, 0) }
	};

	numvertexes = 3;

	// Creates Vertex Buffer
	HR(device->CreateVertexBuffer(
		numvertexes * sizeof(MyVertex), // Length 
		0, // Usage 
		0, // FVF (deprecated) 
		D3DPOOL_MANAGED, // Memory pool 
		&vertexBuffer, // Output to buffer 
		nullptr)); // Use nullptr 

	// Copy to Vertex Buffer
	VOID* pVoid;
	HR(vertexBuffer->Lock(0, 0, &pVoid, 0));
	memcpy(pVoid, vertices, sizeof(vertices));
	HR(vertexBuffer->Unlock());

	// Deactivate Culling, since the scene will rotate
	HR(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

	// Turn 3D Illumination off.
	HR(device->SetRenderState(D3DRS_LIGHTING, FALSE));

	// Initializes shader.
	std::string errors = shader.compile(device);
	if (!errors.empty())
	{
		MessageBoxA(0, errors.c_str(), 0, 0);
	}
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
	//Gira 360 graus por segundo
	angle += 360 * time;
	while (angle >= 360)
		angle -= 360;
	return AbstractGameLoop::process(time);
}

void Scene::paint(IDirect3DDevice9* device)
{
    //Clear screen
	device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 20, 80), 1.0f, 0);

    device->BeginScene();    // Begins Scene

	// Drawing code BEGIN

	// Sets vertex declaration to the one created on the setup() method.
	HR(device->SetVertexDeclaration(vertexDeclaration));
	
	//--------------------------------------------------
	// World transform
	//--------------------------------------------------

	// Translation Matrix
	D3DXMATRIX world;

	D3DXMatrixTranslation(&world, 1, 1, 0);

	D3DXMATRIX rotation;
	D3DXMatrixIdentity(&rotation);
	D3DXMatrixRotationY(&rotation, D3DXToRadian(angle));

	world = rotation * world;

	//--------------------------------------------------
	// View transform
	//--------------------------------------------------
	D3DXMATRIX view;
	//D3DXMatrixIdentity(&view);	
	D3DXMatrixLookAtLH(&view,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f), // posição da câmera
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
	// Stream Source
	//--------------------------------------------------
	// Sets stream source
	HR(device->SetStreamSource(
		0, // Stream number 
		vertexBuffer, // Data 
		0, // Offset 
		sizeof(MyVertex))); // Vertex data size

	//--------------------------------------------------
	// Shader
	//--------------------------------------------------
	shader.setTechnique("TransformTech");

	shader.setMatrix("World", world);
	shader.setMatrix("View", view);
	shader.setMatrix("Projection", projection);

	//--------------------------------------------------
	// Primitives Drawing
	//--------------------------------------------------

	shader.execute([](IDirect3DDevice9* device)
	{
		// Draws primitive (triangle)
		HR(device->DrawPrimitive(
			D3DPT_TRIANGLELIST, // Primitive 
			0, // First index
			1)); // Quantity 
	});

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
	// Release Mesh
	vertexDeclaration->Release();
	vertexBuffer->Release();
}