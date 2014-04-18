#include "mage/GameWindow.h"
#include "Scene.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR      pCmdLine,
                   int       nShowCmd)
{
	mage::GameWindow& window = mage::GameWindow::get();

	if (window.setup(hInstance, nShowCmd, _T("Trabalho - Jogos 3D I - Direct X"), 
		100, 100, 800, 600))
	{		
		window.run(new Scene());
	}

	window.shutDown();
}