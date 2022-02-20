#include "Texture.h"
#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& FilePath, const std::string& Type)
    : mTextureID(0)
{
    // Load texture with stb_image.
    mData = stbi_load(FilePath.c_str(), &mWidth, &mHeight, &mNumberOfChannels, 0);

    if (mData)
    {
        CRESCENT_CORE_INFO("Loaded texture from file: {}", FilePath);
    }
    else
    {
        CRESCENT_CORE_ERROR("Texture loading from file error : {}", FilePath);
    }
}

Texture::Texture(int Width, int Height, GLenum Format)
    : mWidth(Width), mHeight(Height), mTextureID(0)
{
    // Generate texture
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, Format, mWidth, mHeight, 0, Format, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::GenerateTexture()
{
    // Generate texture ID on the GPU
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    if (mData)
    {
        GLenum Format;
        switch (mNumberOfChannels)
        {
            case 1: Format = GL_RED; break;
            case 3: Format = GL_RGB; break;
            case 4: Format = GL_RGBA; break;
            default: Format = GL_RGB; break;
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
        glTexImage2D(GL_TEXTURE_2D, 0, Format, mWidth, mHeight, 0, Format, GL_UNSIGNED_BYTE, mData);
        glGenerateMipmap(GL_TEXTURE_2D);
            

    }
    bGenerated = true;
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::BindTextureUnit(Shader* Shader, const std::string& Name, uint32_t Unit)
{
    // Get uniform location
    Shader->SetUniformInt(Name, Unit);
    glActiveTexture(GL_TEXTURE0 + Unit);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

// Release texture program side.
void Texture::Release()
{
    Destroy();
    FreeData();
}

// Destroy texture GPU side.
void Texture::Destroy()
{
    glDeleteTextures(1, &mTextureID);
    bGenerated = false;
}

void Texture::FreeData()
{
    stbi_image_free(mData);
}
