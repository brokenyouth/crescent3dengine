#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& Vertices, std::vector<uint32_t>& Indices)
    : mVertices(Vertices), mVertexIndices(Indices)
{
    mVertexCount = mVertexIndices.size();
}

void Mesh::BuildMesh()
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVertexBuffer);
    glGenBuffers(1, &mIndexBuffer);
    glGenBuffers(1, &mTextureBuffer);

    glBindVertexArray(mVAO);
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);
    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexIndices.size() * sizeof(uint32_t), mVertexIndices.data(), GL_STATIC_DRAW);
    // Attrib pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexUV));
}

void Mesh::Release() const
{
    glBindVertexArray(mVAO);
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteBuffers(1, &mTextureBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteVertexArrays(1, &mVAO);
    glBindVertexArray(0);
}

void Mesh::AddTexture(Texture* Texture)
{
	mTextures.push_back(Texture);
}
