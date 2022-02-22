#include "Skybox.h"

#include "Logger.h"

#include <fstream>
#include <string>
#include <exception>

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

Skybox::Skybox()
{
	mShader = ResourceManager::GetInstance()->GetShader("skyshader");
}

Skybox::~Skybox()
{
	Release();
}

void Skybox::LoadFromFile(std::string Path)
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

		TextureFilePath = std::string("assets/") + TextureFilePath;
		if (RM->LoadTexture(TextureFilePath, std::string("skybox")))
		{
			mTextures[Side] = RM->GetTexture(TextureFilePath);
			CRESCENT_CORE_INFO("Side {} => {}", Side, TextureFilePath);
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

	glGenVertexArrays(1, &mSkyVAO);
	glGenBuffers(1, &mSkyVBO);
	glBindVertexArray(mSkyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mSkyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}

void Skybox::Draw(glm::mat4 Projection, glm::mat4 View)
{
	CRESCENT_CORE_INFO("TextureID => {}", mTextureId);
	glm::mat4 _View = glm::mat4(glm::mat3(View));
	glDepthFunc(GL_LEQUAL);
	mShader->Bind();

	mShader->SetUniformMat4("ProjectionMatrix", Projection);
	mShader->SetUniformMat4("ViewMatrix", _View);

	glBindVertexArray(mSkyVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
	mShader->Unbind();
}

void Skybox::Release()
{
	glDeleteVertexArrays(1, &mSkyVAO);
	glDeleteBuffers(1, &mSkyVBO);
}
