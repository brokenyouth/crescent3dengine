#include "Model.h"
#include "ResourceManager.h"
#include "Logger.h"

Model::Model(std::string FilePath) : mModelFullPath(FilePath)
{
    LoadModel(FilePath);
}

Model::~Model()
{
    Release();
}

void Model::PrepareModel()
{
    for (auto& _Mesh : mMeshes)
    {
        _Mesh->BuildMesh();
        for (auto& _Texture : _Mesh->GetTextures())
        {
            if (_Texture->bGenerated == false)
            {
                _Texture->GenerateTexture();
            }
        }
    }
    bReady = true;
    CRESCENT_CORE_INFO("Model {} : READY!", mModelFullPath);
}

void Model::Release()
{
    for (auto& _Mesh : mMeshes)
    {
        _Mesh->Release();
    }
}

std::string Model::GetModelPath() const
{
    return mModelFullPath;
}

void Model::LoadModel(std::string& FilePath)
{
    Assimp::Importer Importer;
    const aiScene* scene = Importer.ReadFile(FilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        CRESCENT_CORE_ERROR("Model loading error: {}", Importer.GetErrorString());
        return;
    }
    CRESCENT_CORE_WARN("Loading model: {}", FilePath);
    mModelFilePath = FilePath.substr(0, FilePath.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{
    // process node's sub-meshes
    for (auto i = 0; i < Node->mNumMeshes; i++)
    {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        ProcessMesh(Mesh, Scene);
    }
    // recursive call for children
    for (auto i = 0; i < Node->mNumChildren; i++)
    {
        ProcessNode(Node->mChildren[i], Scene);
    }
}

void Model::ProcessMesh(aiMesh* AiMesh, const aiScene* Scene)
{
    ResourceManager* RMInstance = ResourceManager::GetInstance();
    auto Iterator = RMInstance->AssimpMeshesMap.find(AiMesh);
    if (Iterator != RMInstance->AssimpMeshesMap.end())
    {
        // Mesh already created/loaded
        mMeshes.push_back(Iterator->second);
        return;
    }

    std::vector<Vertex> Vertices;
    std::vector<uint32_t> Indices;

    // Deal with vertices
    for (auto i = 0; i < AiMesh->mNumVertices; ++i)
    {
        // create a new vertex object
        Vertex Vertex;

        // Position
        glm::vec3 Position(1.0f);
        Position.x = AiMesh->mVertices[i].x;
        Position.y = AiMesh->mVertices[i].y;
        Position.z = AiMesh->mVertices[i].z;
        Vertex.Position = Position;
        Vertex.Color = glm::vec3(1.0f, 1.0f, 1.0f);

        // Normal
        glm::vec3 Normal(1.0f);
        if (AiMesh->mNormals != nullptr)
        {
            Normal.x = AiMesh->mNormals[i].x;
            Normal.y = AiMesh->mNormals[i].y;
            Normal.z = AiMesh->mNormals[i].z;
        }
        
        Vertex.Normal = Normal;

        // Texture UVs (if any)
        if (AiMesh->mTextureCoords[0])
        {
            glm::vec2 TexUV(1.0f);
            TexUV.x = AiMesh->mTextureCoords[0][i].x;
            TexUV.y = AiMesh->mTextureCoords[0][i].y;
            Vertex.TexUV = TexUV;
        }
        else // else just give it default coords
        {
            Vertex.TexUV = glm::vec2(0.0f, 0.0f);
        }

        // Push this vertex to the vertices list
        Vertices.push_back(Vertex);
    }
    // Deal with indices
    for (auto i = 0; i < AiMesh->mNumFaces; ++i)
    {
        aiFace Face = AiMesh->mFaces[i];
        for (auto j = 0; j < Face.mNumIndices; ++j)
        {
            Indices.push_back(Face.mIndices[j]);
        }
    }
    
    MeshPtr InMesh = std::make_shared<Mesh>(Vertices, Indices);

    // Materials
    if (AiMesh->mMaterialIndex >= 0)
    {
        aiMaterial* Material = Scene->mMaterials[AiMesh->mMaterialIndex];
        std::vector<Texture*> DiffuseTextures = LoadTextures(Material, aiTextureType_DIFFUSE, "diffuse");
        std::vector<Texture*> SpecularTextures = LoadTextures(Material, aiTextureType_DIFFUSE, "specular");

        for (auto& DiffuseTexture : DiffuseTextures)
        {
            InMesh->AddTexture(DiffuseTexture);
        }
        for (auto& SpecularTexture : SpecularTextures)
        {
            InMesh->AddTexture(SpecularTexture);
        }
    }
    mMeshes.push_back(InMesh);
    RMInstance->AssimpMeshesMap[AiMesh] = InMesh;
    
}

std::vector<Texture*> Model::LoadTextures(aiMaterial* Material, aiTextureType EType, const std::string& TextureType)
{
    std::vector<Texture*> Textures = {};
    ResourceManager* RMInstance = ResourceManager::GetInstance();
    for (auto i = 0; i < Material->GetTextureCount(EType); ++i)
    {
        aiString AiTextureName;
        Material->GetTexture(EType, i, &AiTextureName);
        std::string TextureName = std::string(AiTextureName.C_Str()); // convert aiString to std::string cuz our TextureManager deals with std::strings

        Texture* InTexture = nullptr;
        if (InTexture = RMInstance->GetTexture(mModelFilePath + "/" + TextureName))
        {
            Textures.push_back(InTexture);
        }
        else
        {
            RMInstance->LoadTexture((mModelFilePath + "/" + TextureName), TextureType);
            InTexture = RMInstance->GetTexture(mModelFilePath + "/" + TextureName);
            Textures.push_back(InTexture);
        }
    }

    return Textures;
}
