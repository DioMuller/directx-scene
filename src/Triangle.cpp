#include "Triangle.h"
#include "mage/HandleError.h"

void Triangle::setup(IDirect3DDevice9* device)
{
	running = true;

	//Passo A1 - Declaração do formatodo vértice
	//FLOAT x, y, z;
    //DWORD color;
	D3DVERTEXELEMENT9 decl[] = {
	   {0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0},
	   {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
	   D3DDECL_END()
	};
	vertexDeclaration = NULL;
	HR(device->CreateVertexDeclaration(decl, &vertexDeclaration));

	//Passo A2 - Criação da malha
	MyVertex vertices[] =
	{
        { 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), }
	};

	//Passo A3 - Criação do Vertex Buffer;
	HR(device->CreateVertexBuffer(		
		3 * sizeof(MyVertex), //Length
		0,					  //Usage
		0,					  //FVF (old way)
		D3DPOOL_MANAGED,	  //Memory pool
		&vertexBuffer,		  //saída: Buffer
		NULL));				  //Use null

	//Passo A4 - Cópia da malha para o Vertex Buffer
	VOID* pVoid;    

	//Travamos a placa e obtemos acesso exclusivo à memória   
	HR(vertexBuffer->Lock(0, 0, &pVoid, 0));

	//Copiamos o buffer para a placa
	memcpy(pVoid, vertices, sizeof(vertices));

	//Liberamos a placa
	HR(vertexBuffer->Unlock());
}

void Triangle::paint(IDirect3DDevice9* device)
{
    HR(device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));

	//Passo B - Desenho do Vertex Buffer
	HR(device->BeginScene());
		HR(device->SetVertexDeclaration(vertexDeclaration));		
		HR(device->SetStreamSource(0,						//Número do stream
			vertexBuffer,									//Dados
			0,												//Offset
			sizeof(MyVertex)));								//Tamanho do dado
		HR(device->DrawPrimitive(D3DPT_TRIANGLELIST,		//Primitiva
			0,												//Vértice inicial
			1));											//Quantidade
	HR(device->EndScene());

	HR(device->Present(NULL, NULL, NULL, NULL));
}
void Triangle::shutDown(IDirect3DDevice9* device)
{
	//Passo C - Liberação da malha
	vertexDeclaration->Release();
	vertexBuffer->Release();
}

void Triangle::processEvent(const mage::WindowsEvent& evt)
{
	if (evt.type == WM_KEYDOWN && evt.wParam == VK_ESCAPE)
		running = false;	
}