#pragma once

#include <unordered_map>
#include <string>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#include <assimp/mesh.h>

enum class ResourceType
{
	Texture,
	Shader
};

class ResourceManager
{
private:
	static ResourceManager* sInstance;
	std::unordered_map<std::string, TexturePtr> mTextures;
	std::unordered_map<std::string, ShaderPtr> mShaders;
public:
	std::unordered_map<aiMesh*, MeshPtr> AssimpMeshesMap;
private:
	ResourceManager();
	virtual ~ResourceManager() {}

public:
	void Release();

	static ResourceManager* GetInstance();
	Texture* GetTexture(const std::string& TextureFilePath) const;
	Shader* GetShader(const std::string& Name) const;

	bool LoadTexture(const std::string& FilePath, const std::string& Type);
	bool LoadShader(const std::string& Name, const std::string& VertexFilePath, const std::string& FragmentFilePath);

private:
	void ReleaseTextures() const;
	void ReleaseShaders() const;
};

