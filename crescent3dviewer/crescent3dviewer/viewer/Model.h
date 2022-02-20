#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
private:
	std::vector<MeshPtr> mMeshes;
	std::string mModelFilePath;
	std::string mModelFullPath;
public:
	Model(std::string FilePath);
	~Model();

public:
	bool bReady = false;
	void PrepareModel();
	inline std::vector<MeshPtr> GetMeshes() const { return mMeshes; }
	void Release();

	std::string GetModelPath() const;
private:
	void LoadModel(std::string& FilePath);
	void ProcessNode(aiNode* Node, const aiScene* Scene);
	void ProcessMesh(aiMesh* Mesh, const aiScene* Scene);
	std::vector<Texture*> LoadTextures(aiMaterial* Material, aiTextureType EType, const std::string& TextureType);
};

