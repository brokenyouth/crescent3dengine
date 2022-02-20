#pragma once

#include <memory>
#include <vector>

#include "Vertex.h"
#include "Texture.h"

class Mesh
{
private:
    uint32_t mVAO = 0;
    uint32_t mTextureBuffer = 0;
    uint32_t mIndexBuffer = 0;
    uint32_t mVertexBuffer = 0;
    uint32_t mVertexCount = 0;
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mVertexIndices;
    std::vector<Texture*> mTextures;

public:
    Mesh(std::vector<Vertex>& Vertices, std::vector<uint32_t>& Indices);
    virtual ~Mesh() {}

    void BuildMesh();

    void Release() const;
    void AddTexture(Texture* Texture);
    inline uint32_t GetVAO() const { return mVAO; }
    inline uint32_t GetVertexCount() const { return mVertexCount; }
    inline std::vector<Texture*> GetTextures() const { return mTextures; }
};

typedef std::shared_ptr<Mesh> MeshPtr;

