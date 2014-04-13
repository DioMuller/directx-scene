#pragma once
#include "mage/IGameLoop.h"

class MyGame : public mage::IGameLoop
{
	private:
		bool running;
	public:
		MyGame(void);
		~MyGame(void);

		virtual void setup(IDirect3DDevice9* device);
		virtual void processEvent(const mage::WindowsEvent& msg);
		virtual bool process(float time);
		virtual void paint(IDirect3DDevice9* device);
		virtual void onLostDevice();
		virtual void onRestoreDevice(IDirect3DDevice9* device);
		virtual void shutDown(IDirect3DDevice9* device);
};

