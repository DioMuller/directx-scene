#pragma once
#include <map>
#include <d3dx9.h>

class TextureLoader
{
	////////////////////////////////////
	// Attributes
	////////////////////////////////////
	private:
		static std::map<std::wstring, IDirect3DTexture9*> textures;

	////////////////////////////////////
	// Methods
	////////////////////////////////////
	public:
		static IDirect3DTexture9* LoadTexture(IDirect3DDevice9* device, std::wstring texture);
		static void ReleaseTexture(std::wstring texture);
};

