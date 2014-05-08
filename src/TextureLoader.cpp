#include "TextureLoader.h"
#include "mage/HandleError.h"


std::map<std::wstring, IDirect3DTexture9*> TextureLoader::textures = std::map<std::wstring, IDirect3DTexture9*>();

IDirect3DTexture9* TextureLoader::LoadTexture(IDirect3DDevice9* device, std::wstring textureFile)
{
	if (textures[textureFile] != nullptr) return textures[textureFile];

	IDirect3DTexture9* texture;
	HR(D3DXCreateTextureFromFile(device, textureFile.c_str(), &texture));
	textures[textureFile] = texture;

	return texture;
}

void TextureLoader::ReleaseTexture(std::wstring textureFile)
{
	if (textures[textureFile] == nullptr) return;

	textures[textureFile]->Release();
	//delete textures[textureFile]; ERROR
	textures[textureFile] = nullptr;
}