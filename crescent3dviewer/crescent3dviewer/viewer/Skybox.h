#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

#include "Texture.h"
#include "Mesh.h"
#include "ResourceManager.h"


class Skybox
{
private:
	std::unordered_map<std::string, Texture*> mTextures;
	Shader* mShader;

	uint32_t mTextureId = 0;
	uint32_t mSkyVAO = 0;
	uint32_t mSkyVBO = 0;

public:
	Skybox();
	~Skybox();

public:
	void LoadFromFile(std::string Path);
	void Prepare();

	void Draw(glm::mat4 Projection, glm::mat4 View);
	void Release();

};

