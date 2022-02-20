#include "Skybox.h"

#include <fstream>
#include <string>
#include <exception>

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

void Skybox::LoadFromFile(std::string& Path)
{
	ResourceManager* RM = ResourceManager::GetInstance();

	std::ifstream InFile(Path.c_str());
	std::string Line;

	while (std::getline(InFile, Line))
	{
		std::istringstream Iss(Line);
		std::string Side, TextureFilePath;

		if (!(Iss >> Side >> TextureFilePath))
		{
			throw std::runtime_error("Error occured while trying to load skybox config file.");
		}

		if (RM->LoadTexture(std::string("assets/") + TextureFilePath, std::string("skybox")))
		{
			mTextures[Side] = RM->GetTexture(TextureFilePath);
		}
	}
}

void Skybox::Prepare()
{
	std::vector<std::string> Sides = { "right", "left", "top", "bottom", "back", "front" };

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE0, mTextureId);


	for (auto i = 0; i < Sides.size(); i++)
	{
		Texture* SideTexture = mTextures[Sides[i]];
		unsigned char* Data = SideTexture->GetData();
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, SideTexture->GetWidth(),
			SideTexture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Skybox::Release()
{

}
