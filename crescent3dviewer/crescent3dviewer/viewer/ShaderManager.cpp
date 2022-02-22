#include "ShaderManager.h"
#include "ResourceManager.h"

ShaderManager* ShaderManager::sInstance = nullptr;

ShaderManager::ShaderManager()
{
	Initialize();
}

ShaderManager::~ShaderManager()
{
	Release();
}

void ShaderManager::Initialize()
{
	ResourceManager* RM = ResourceManager::GetInstance();
	/* --------------------------------------------- */

	RM->LoadShader("default", "./shaders/default_vs.glsl", "./shaders/default_fs.glsl");
	Shader* DefaultShader = RM->GetShader("default");
	DefaultShader->CreateUniform("ProjectionMatrix");
	DefaultShader->CreateUniform("ViewMatrix");
	DefaultShader->CreateUniform("ModelMatrix");

	mShaders["default"] = DefaultShader;

	/* --------------------------------------------- */

	RM->LoadShader("skyshader", "./shaders/skybox_vs.glsl", "./shaders/skybox_fs.glsl");
	Shader* SkyShader = RM->GetShader("skyshader");
	SkyShader->CreateUniform("ProjectionMatrix");
	SkyShader->CreateUniform("ViewMatrix");

	mShaders["skybox"] = SkyShader;

	/* --------------------------------------------- */

}

void ShaderManager::Release()
{
	if (ShaderManager::sInstance)
	{
		delete ShaderManager::sInstance;
		ShaderManager::sInstance = nullptr;
	}
}

ShaderManager* ShaderManager::GetInstance()
{
	if (sInstance)
	{
		return sInstance;
	}
	return new ShaderManager();
}

ShaderManager* ShaderManager::Get()
{
	return GetInstance();
}

Shader* ShaderManager::GetShader(std::string& InShaderName)
{
	auto Iterator = mShaders.find(InShaderName);
	if (Iterator != mShaders.end())
	{
		return Iterator->second;
	}
	return nullptr;
}
