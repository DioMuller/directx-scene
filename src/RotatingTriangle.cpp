#include "RotatingTriangle.h"
#include "mage/GameWindow.h"
#include "mage/HandleError.h"

RotatingTriangle::RotatingTriangle() : shader(_T("SimpleShader.hlsl")) {}

void RotatingTriangle::setup(IDirect3DDevice9* device)
{
	// SHADER
	std::string errors = shader.compile(device);
	if (!errors.empty())
	{
		MessageBoxA(0, errors.c_str(), 0, 0);
	}

	// ORIGINAL
	running = true;
	angle = 0;

	//Passo A1 - Declara��o do formatodo v�rtice
	//FLOAT x, y, z;
    //DWORD color;
	D3DVERTEXELEMENT9 decl[] = {
	   {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	   {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	   D3DDECL_END()
	};
	vertexDeclaration = NULL;
	HR(device->CreateVertexDeclaration(decl, &vertexDeclaration));

	//Passo A2 - Cria��o da malha
	MyVertex vertices[] =
	{		
		{D3DXVECTOR3(3.0f, -3.0f, 0.0f), D3DCOLOR_XRGB(0, 0, 255) },
        {D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DCOLOR_XRGB(0, 255, 0) },
        {D3DXVECTOR3(-3.0f, -3.0f, 0.0f), D3DCOLOR_XRGB(255, 0, 0) }
	};

	//Passo A3 - Cria��o do Vertex Buffer;
	HR(device->CreateVertexBuffer(3 * sizeof(MyVertex), 0, 0, D3DPOOL_MANAGED,
		&vertexBuffer, NULL));

	//Passo A4 - C�pia da malha para o Vertex Buffer
	VOID* pVoid;    
	HR(vertexBuffer->Lock(0, 0, &pVoid, 0));
	memcpy(pVoid, vertices, sizeof(vertices));
	HR(vertexBuffer->Unlock());

		
	//Desativamos o culling para exibir o tri�ngulo quando estiver de costas
	HR(device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));

	//Desligamos a ilumina��o 3D
	HR(device->SetRenderState(D3DRS_LIGHTING, FALSE));	
	
}

bool RotatingTriangle::process(float time) 
{
	//Gira 360 graus por segundo
	angle += 360 * time;
	while (angle >= 360)
		angle -= 360;
	return AbstractGameLoop::process(time);
}

void RotatingTriangle::paint(IDirect3DDevice9* device)
{

    HR(device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));

	//Passo B - Desenho do Vertex Buffer
	HR(device->BeginScene());

		//--------------------------------------------------
		// World transform
		// O tri�ngulo ficar� girado em "angle" graus
		// Tamb�m moveremos ele para a posi��o x=1 y=1 z=1
		//--------------------------------------------------

		//Criamos a matriz de transla��o
		D3DXMATRIX world;
		//D3DXMatrixIdentity(&world);	

		//Definimos uma afastamos o tri�ngulo em (1,1,0)
		D3DXMatrixTranslation(&world, 1, 1, 0);

		//Criamos a matriz de rota��o
		D3DXMATRIX rotation;
		D3DXMatrixIdentity(&rotation);

		//Definimos uma rota��o em y
		D3DXMatrixRotationY(&rotation, D3DXToRadian(angle));		

		//Combinamos as duas matrizes	
		world = rotation * world;
		//D3DXMatrixMultiply(&world, &rotation, &world);

		//Definimos a matriz world
		//HR(device->SetTransform(D3DTS_WORLD, &world));

		//--------------------------------------------------
		//Transforma��o da vis�o.
		//Vamos somente afastar a c�mera 10 no z.
		//--------------------------------------------------
		D3DXMATRIX view;
		//D3DXMatrixIdentity(&view);	
		D3DXMatrixLookAtLH(&view,
			&D3DXVECTOR3 (0.0f, 0.0f, 10.0f), // posi��o da c�mera
            &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),  // local para onde olha
            &D3DXVECTOR3 (0.0f, 1.0f, 0.0f)); // topo do mundo
		//HR(device->SetTransform(D3DTS_VIEW, &view));

		//--------------------------------------------------
		// Transforma��o da proje��o
		//--------------------------------------------------
		D3DXMATRIX projection;     // the projection transform matrix
		D3DXMatrixPerspectiveFovLH(
			&projection,
			D3DXToRadian(60),					 // Campo de vis�o horizontal
			mage::GameWindow::get().getAspect(), // aspect ratio
			1.0f,								 // Plano near
			100.0f);							 // Plano far
		
		//HR(device->SetTransform(D3DTS_PROJECTION, &projection));

		//Agora sim, fazemos o desenho
		HR(device->SetVertexDeclaration(vertexDeclaration));		
		HR(device->SetStreamSource(0,						//N�mero do stream
			vertexBuffer,									//Dados
			0,												//Offset
			sizeof(MyVertex)));								//Tamanho do dado

		// SHADER MAGIC

		//Obtemos a t�cnica
		shader.setTechnique("TransformTech");

		//Definimos os par�metros
		shader.setMatrix("World", world);
		shader.setMatrix("View", view);
		shader.setMatrix("Projection", projection);

		//Realizamos as passadas, desenhando
		shader.execute([](IDirect3DDevice9* device)
		{
			HR(device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1));
		});
		// END SHADER MAGIC

	HR(device->EndScene());

	HR(device->Present(NULL, NULL, NULL, NULL));
}
void RotatingTriangle::shutDown(IDirect3DDevice9* device)
{
	//Passo C - Libera��o da malha
	vertexDeclaration->Release();
	vertexBuffer->Release();
}

void RotatingTriangle::processEvent(const mage::WindowsEvent& evt)
{
	if (evt.type == WM_KEYDOWN && evt.wParam == VK_ESCAPE)
		running = false;	
}