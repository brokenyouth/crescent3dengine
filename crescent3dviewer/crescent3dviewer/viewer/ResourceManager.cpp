#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"

#include "Logger.h"

ResourceManager* ResourceManager::sInstance = nullptr;

ResourceManager::ResourceManager()
{
	CRESCENT_CORE_INFO("Resource Manager initialized.");
}


void ResourceManager::Release()
{
	if (ResourceManager::sInstance)
	{
		ReleaseTextures();
		ReleaseShaders();
		delete sInstance;
		sInstance = nullptr;

		CRESCENT_CORE_INFO("Resource Manager released.");
	}
	else
	{
		CRESCENT_CORE_INFO("Resource Manager already released.");
	}
}

bool ResourceManager::LoadTexture(const std::string& FilePath, const std::string& Type)
{
	auto Iterator = mTextures.find(FilePath);
	if (Iterator != mTextures.end())
	{
		CRESCENT_CORE_INFO("Texture already loaded : {} - Skipping...", FilePath);
		return false;
	}
	TexturePtr InTexture = std::make_shared<Texture>(FilePath, Type);
	mTextures[FilePath] = InTexture;
	return true;

}

bool ResourceManager::LoadShader(const std::string& Name, const std::string& VertexFilePath, const std::string& FragmentFilePath)
{
	auto Iterator = mShaders.find(Name);
	if (Iterator != mShaders.end())
	{
		CRESCENT_CORE_INFO("Shader already loaded : {} - Skipping...", Name);
		return false;
	}
	ShaderPtr InShader = std::make_shared<Shader>(VertexFilePath.c_str(), FragmentFilePath.c_str());
	mShaders[Name] = InShader;
	return true;
}

void ResourceManager::ReleaseTextures() const
{
	auto Iterator = mTextures.begin();
	while (Iterator != mTextures.end())
	{
		Iterator->second->Release();
		Iterator++;
	}
}

void ResourceManager::ReleaseShaders() const
{
	auto Iterator = mShaders.begin();
	while (Iterator != mShaders.end())
	{
		Iterator->second->Release();
		Iterator++;
	}
}

ResourceManager* ResourceManager::GetInstance()
{
	if (sInstance)
		return sInstance;
	else
	{
		sInstance = new ResourceManager();
		return sInstance;
	}
}

Texture* ResourceManager::GetTexture(const std::string& TextureFilePath) const
{
	auto Iterator = ResourceManager::sInstance->mTextures.find(TextureFilePath);
	if (Iterator != ResourceManager::sInstance->mTextures.end())
	{
		return Iterator->second.get();
	}
	return nullptr;
}

Shader* ResourceManager::GetShader(const std::string& Name) const
{
	auto Iterator = ResourceManager::sInstance->mShaders.find(Name);
	if (Iterator != ResourceManager::sInstance->mShaders.end())
	{
		return Iterator->second.get();
	}
	return nullptr;
}
