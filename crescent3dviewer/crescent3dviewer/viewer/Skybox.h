#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

#include "Texture.h"
#include "ResourceManager.h"

class Skybox
{
private:
	std::unordered_map<std::string, Texture*> mTextures;
	uint32_t mTextureId = 0;

public:
	Skybox();
	~Skybox();

public:
	void LoadFromFile(std::string& Path);
	void Prepare();

	void Release();

};

