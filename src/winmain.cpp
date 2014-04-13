#include "mage/GameWindow.h"
#include "MyGame.h"

// Equivalente windows do "Main"
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR      pCmdLine,
                   int       nShowCmd)
{
	//Obtemos o subsistema da janela
	mage::GameWindow& window = mage::GameWindow::get();
	//Tentamos inicializa-lo.
	if (window.setup(hInstance, nShowCmd, _T("Transformações - Pipeline programável"), 
		100, 100, 800, 600))
	{		
		window.run(new MyGame()); //Se deu certo, roda o game loop
	}

	//Finalizamos o sistema.
	window.shutDown();
}