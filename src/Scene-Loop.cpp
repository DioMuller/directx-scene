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

	int cols = 50;
	int rows = 50;
	int width = 10.0f;
	int height = 10.0f;

	// Generate Plane mesh vertexes and indexes.
	Mesh plane = createPlaneMesh( width, height, cols, rows);
	int indexCount = plane.indexes.size();
	vertexCount = plane.vertexCount;
	triangleCount = (cols - 1) * (rows - 1) * 2; // Two triangles per square

	// Generate Cylinder
	D3DXCreateCylinder(device, 1.5, 1.5, 5, 20, 20, &cilinder, nullptr);

	// Create vertex buffer on the device.
	vertexBuffer = Vertex::createVertexBuffer(device, plane.vertexes);

	// Create index buffer on the device.
	HR(device->CreateIndexBuffer(sizeof(WORD)* indexCount, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuffer, nullptr));

	// Writes indexes on the video memory.
	WORD* pWord;
	HR(indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pWord), 0));
	for (int i = 0; i < indexCount; i++)
		pWord[i] = static_cast<WORD>(plane.indexes[i]);
	HR(indexBuffer->Unlock());

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
	// Stream Source
	//--------------------------------------------------
	// Set vertex declaration
	HR(device->SetVertexDeclaration(Vertex::getDeclaration(device)));

	// Sets stream source
	HR(device->SetStreamSource(
		0, // Stream number 
		vertexBuffer, // Data 
		0, // Offset 
		sizeof(Vertex))); // Vertex data size

	// Set indexes
	HR(device->SetIndices(indexBuffer));

	//--------------------------------------------------
	// Shader
	//--------------------------------------------------
	
	// Get technique
	D3DXHANDLE tech = shader->GetTechniqueByName("TransformTech");
	HR(shader->SetTechnique(tech));

	// Parameter definition
	D3DXHANDLE hWorld = shader->GetParameterByName(0, "World");
	HR(shader->SetMatrix(hWorld, &world));

	D3DXHANDLE hView = shader->GetParameterByName(0, "View");
	HR(shader->SetMatrix(hView, &view));

	D3DXHANDLE hProjection = shader->GetParameterByName(0, "Projection");
	HR(shader->SetMatrix(hProjection, &projection));

	// Passes
	UINT passes = 0;
	HR(shader->Begin(&passes, 0));
	for (UINT i = 0; i < passes; ++i)
	{
		HR(shader->BeginPass(i));
		HR(device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount));
		HR(shader->EndPass());

		HR(cilinder->DrawSubset(0));
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
	// Release Mesh
	vertexBuffer->Release();
}