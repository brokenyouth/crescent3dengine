#pragma once

#include <cstdint>
#include <string>

#include "Shader.h"
#include <GL/glew.h>

class Texture
{
private:
    unsigned char* mData = nullptr;
    int mWidth;
    int mHeight;
    int mNumberOfChannels;
    std::string mType;

public:
    uint32_t mTextureID; // this is opengl texture id
    bool bGenerated = false;
    Texture(const std::string& FilePath, const std::string& Type);
    Texture(int Width, int Height, GLenum Format);

public:
    void GenerateTexture();
    void BindTextureUnit(Shader* Shader, const std::string& Name, uint32_t Unit);
    void Release();
    void Destroy();
    void FreeData();
    inline unsigned char* GetData() const { return mData; }
    inline const uint32_t GetTextureID() const { return mTextureID; }
    inline const int GetWidth() const { return mWidth; }
    inline const int GetHeight() const { return mHeight; }
    inline const int GetNumChannels() const { return mNumberOfChannels; }
    inline const std::string& GetType() const { return mType; }
};

typedef std::shared_ptr<Texture> TexturePtr;
