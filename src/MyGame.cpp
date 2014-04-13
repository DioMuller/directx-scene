#include "MyGame.h"
#include "mage/WindowsEvent.h"
#include "mage/GameWindow.h"

using namespace mage;

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::setup(IDirect3DDevice9* device)
{
	running = true;
}

void MyGame::processEvent(const WindowsEvent& evt)
{
	switch (evt.type)
	{
		case WM_KEYDOWN:
			if( evt.wParam == VK_ESCAPE )
				running = false;
			return;
	}
}

bool MyGame::process(float time)
{
	return running;
}

void MyGame::paint(IDirect3DDevice9* device)
{
    //Limpa a janela de azul escuro
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 20, 80), 1.0f, 0);

    device->BeginScene();    // Começa a cena 3D

    //O código do desenho vai aqui

    device->EndScene();    // Finaliza a cena 3D.

    device->Present(NULL, NULL, NULL, NULL);    // Exibe o quadro recém criado
}

void MyGame::onLostDevice()
{
}

void MyGame::onRestoreDevice(IDirect3DDevice9* device)
{
}

void MyGame::shutDown(IDirect3DDevice9* device)
{
}