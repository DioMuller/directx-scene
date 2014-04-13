#include "WaveGrid.h"
#include "mage/GameWindow.h"
#include "mage/HandleError.h"
#include "mage/TString.h"
#include "WaveGrid.h"

void WaveGrid::setup(IDirect3DDevice9* device)
{
	time = 0;
	running = true;

	//Criação do vertex buffer
	//------------------------
	
	//Criação da malha
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	createTriangleGrid(100, 100, 51, 51, vertices, indices, numTriangles);
	numVertices = vertices.size();
	numIndices = indices.size();

	vertexBuffer = Vertex::createVertexBuffer(device, vertices);	

	HR(device->CreateIndexBuffer(sizeof(WORD) * numIndices, 0, D3DFMT_INDEX16,  
		D3DPOOL_MANAGED, &indexBuffer, NULL));

	WORD* pWord;    
	HR(indexBuffer->Lock(0, 0, reinterpret_cast<void**>(&pWord), 0));
	for (int i = 0; i < numIndices; i++)
		pWord[i] = static_cast<WORD>(indices[i]);	
	HR(indexBuffer->Unlock());

	//Carga do shader
	//---------------
	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(device, _T("wave.fx"), 0, 0, D3DXSHADER_DEBUG, 0, &shader, &errors));
	if(errors)
	{
		MessageBoxA(0, static_cast<char*>(errors->GetBufferPointer()), 0, 0);	
		exit(1);
	}
}

bool WaveGrid::process(float time) 
{
	//Gira 360 graus por segundo
	this->time += time;
	return AbstractGameLoop::process(time);	
}

void WaveGrid::createTriangleGrid(float width, float depth, int cols, int rows,
	std::vector<Vertex>& vertices, std::vector<DWORD>& indices, int& numTriangles)
{	
	//Criação dos vértices
	if (rows < 2 || cols < 2)
		return;

	UINT numVertices = rows * cols;

	//Posiciona no centro do sistema
	FLOAT px = -width * 0.5f;
	FLOAT pz = depth * 0.5f;

	UINT cellRows = rows-1;
	UINT cellCols = cols-1;

	float dx = width / cellCols;
	float dz = depth / cellRows;

	int k = 0;
	for (int i = 0; i < rows; ++i) 
		for (int j = 0; j < cols; ++j) 
		{
			vertices.push_back(Vertex(
				j * dx + px,
				0.0f,
				-i * dz + pz,
				0.4f, 0.4f, 1.0f));
			++k;
		}

	//Criação dos índices

	numTriangles = cellRows*cellCols*2;
	indices.resize(numTriangles * 3);

	k = 0;
	for (DWORD i = 0; i < cellRows; ++i)
		for (DWORD j = 0; j < cellCols; ++j)
		{
			indices[k]   =   i   * cols + j;
			indices[k+1] =   i   * cols + j + 1;
			indices[k+2] = (i+1) * cols + j;
					
			indices[k+3] = (i+1) * cols + j;
			indices[k+4] =   i   * cols + j + 1;
			indices[k+5] = (i+1) * cols + j + 1;

			// next quad
			k += 6;
		}
}

void WaveGrid::paint(IDirect3DDevice9* device)
{
    HR(device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));

	//Passo B - Desenho do Vertex Buffer
	HR(device->BeginScene());
		//--------------------------------------------------
		//Transformação da visão.
		//--------------------------------------------------
		D3DXMATRIX view;
		D3DXMatrixIdentity(&view);	
		D3DXMatrixLookAtLH(&view,
			&D3DXVECTOR3 (0.0f, 30.0f, 50.0f), // posição da câmera
            &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),  // local para onde olha
            &D3DXVECTOR3 (0.0f, 1.0f, 0.0f)); // topo do mundo

		//--------------------------------------------------
		// Transformação da projeção
		//--------------------------------------------------
		D3DXMATRIX projection;     // the projection transform matrix
		D3DXMatrixPerspectiveFovLH(
			&projection,
			D3DXToRadian(60),					 // Campo de visão horizontal
			mage::GameWindow::get().getAspect(), // aspect ratio
			1.0f,								 // Plano near
			5000.0f);							 // Plano far
				
		D3DXMATRIX wvp = view * projection;
		
		//Definimos quem serão os vértices
		HR(device->SetVertexDeclaration(Vertex::getDeclaration(device)));		
		HR(device->SetStreamSource(0, vertexBuffer,	0,	sizeof(Vertex)));
		HR(device->SetIndices(indexBuffer));

		//--------------------------------------------------
		//Aplicação do shader
		//--------------------------------------------------
		//Obtemos a técnica
		D3DXHANDLE tech = shader->GetTechniqueByName("TransformTech");
		HR(shader->SetTechnique(tech));

		//Definimos os parâmetros
		D3DXHANDLE hWVP = shader->GetParameterByName(0, "gWVP");
		HR(shader->SetMatrix(hWVP, &wvp));

		D3DXHANDLE hTime = shader->GetParameterByName(0, "gTime");
		HR(shader->SetFloat(hTime, time));

		//Realizamos as passadas, desenhando
		UINT passadas = 0;
		HR(shader->Begin(&passadas, 0));
			for(UINT i = 0; i < passadas; ++i) 
			{
				HR(shader->BeginPass(i));
					HR(device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, 0, numTriangles));
				HR(shader->EndPass());
			}
		HR(shader->End());
	HR(device->EndScene());	
	HR(device->Present(NULL, NULL, NULL, NULL));
}
void WaveGrid::shutDown(IDirect3DDevice9* device)
{
	//Passo C - Liberação da malha
	Vertex::releaseDeclaration();
	shader->Release();
	vertexBuffer->Release();
	indexBuffer->Release();
}

void WaveGrid::processEvent(const mage::WindowsEvent& evt)
{
	if (evt.type == WM_KEYDOWN && evt.wParam == VK_ESCAPE)
		running = false;	
}