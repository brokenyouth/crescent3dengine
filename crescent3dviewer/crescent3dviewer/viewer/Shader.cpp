#include "Shader.h"
#include "Logger.h"

#include <GL/glew.h>

Shader::Shader(const char* VertexPath, const char* FragmentPath)
{
    mUniformsMap = std::map<std::string, int>();
    mProgramId = -1;
    /* Load shaders from disk */
    std::string VertShaderCode = LoadShaderFromFile(VertexPath);
    std::string FragShaderCode = LoadShaderFromFile(FragmentPath);

    /* Compile shaders */
    const char* VertShaderString = VertShaderCode.c_str();
    const char* FragShaderString = FragShaderCode.c_str();

    int Success;
    char Log[512];
    /* vertex shader */
    mVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(mVertexShaderId, 1, &VertShaderString, nullptr);
    glCompileShader(mVertexShaderId);
    CheckCompilationErrors(mVertexShaderId, "VERTEX", GetShaderName(VertexPath));
    /* fragment shader */
    mFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(mFragmentShaderId, 1, &FragShaderString, nullptr);
    glCompileShader(mFragmentShaderId);
    CheckCompilationErrors(mFragmentShaderId, "FRAGMENT", GetShaderName(FragmentPath));
    /* program */
    mProgramId = glCreateProgram();
    glAttachShader(mProgramId, mVertexShaderId);
    glAttachShader(mProgramId, mFragmentShaderId);
    glLinkProgram(mProgramId);
    CheckCompilationErrors(mProgramId, "PROGRAM", "");

    /* clean up */
    Release();

    if (mProgramId != -1)
        CRESCENT_CORE_INFO("[SHADER] {} and {} loaded.", GetShaderName(VertexPath), GetShaderName(FragmentPath));
}

Shader::~Shader()
{
    
}

void Shader::Use()
{
    Bind();
}

void Shader::Bind()
{
    glUseProgram(mProgramId);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::Release()
{
    Unbind();
    glDeleteShader(mVertexShaderId);
    glDeleteShader(mFragmentShaderId);
}

void Shader::CreateUniform(const std::string& Name)
{
    int UniformLoc = glGetUniformLocation(mProgramId, Name.c_str());
    if (UniformLoc < 0)
        CRESCENT_CORE_ERROR("Uniform {} could not be found in program : {}.", Name, mProgramId);

    auto Temp = mUniformsMap.find(Name.c_str());
    if (Temp == mUniformsMap.end()) {  // if not found
        mUniformsMap.insert(std::pair<std::string, int>(Name, UniformLoc));
    }
}

void Shader::SetUniformMat4(const std::string& Name, const glm::mat4& Value)
{
    int Location = -1;
    auto Temp = mUniformsMap.find(Name);
    if (Temp != mUniformsMap.end())
        Location = Temp->second;
    if (Location >= 0)
    {
        glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Value));
    }
}

void Shader::SetUniformInt(const std::string& Name, uint32_t Value)
{
    int Location = -1;
    auto Temp = mUniformsMap.find(Name);
    if (Temp != mUniformsMap.end())
        Location = Temp->second;
    if (Location >= 0)
    {
        glUniform1i(Location, Value);
    }
}

void Shader::SetUniformVec3(const std::string& Name, const glm::vec3& Value)
{
    int Location = -1;
    auto Temp = mUniformsMap.find(Name);
    if (Temp != mUniformsMap.end())
        Location = Temp->second;
    if (Location >= 0)
    {
        glUniform3fv(Location, 1, &Value[0]);
    }
}

void Shader::SetUniformFloat(const std::string& Name, float Value)
{
    int Location = -1;
    auto Temp = mUniformsMap.find(Name);
    if (Temp != mUniformsMap.end())
        Location = Temp->second;
    if (Location >= 0)
    {
        glUniform1f(Location, Value);
    }
}

std::string Shader::LoadShaderFromFile(const char* ShaderPath) const
{
    std::string ShaderCode = "";
    std::ifstream ShaderFile;
    ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        ShaderFile.open(ShaderPath);
        std::stringstream ShaderStream;
        ShaderStream << ShaderFile.rdbuf();
        ShaderFile.close();
        ShaderCode = ShaderStream.str(); // stream to string
    }
    catch (const std::ifstream::failure& e)
    {
        CRESCENT_CORE_ERROR("[SHADER] {} : an error occured while reading this file.", GetShaderName(ShaderPath));
    }
    return ShaderCode;
}

std::string Shader::GetShaderName(const char* ShaderPath) const
{
    std::string PathString = std::string(ShaderPath);
    const size_t LastSlashIndex = PathString.find_last_of("/");
    if (std::string::npos != LastSlashIndex)
    {
        PathString.erase(0, LastSlashIndex + 1);
    }
    return PathString;
}

void Shader::CheckCompilationErrors(GLuint Shader, const std::string& Type, const std::string& ShaderName)
{
    int Success;
    char InfoLog[1024];
    if (Type != "PROGRAM")
    {
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
        if (!Success)
        {
            glGetShaderInfoLog(Shader, 1024, nullptr, InfoLog);
            CRESCENT_CORE_ERROR("[SHADER] {} - compilation error : {}", ShaderName, Type);
            CRESCENT_CORE_WARN("[SHADER] {} : {}", ShaderName, InfoLog);
        }
    }
    else
    {
        glGetProgramiv(Shader, GL_LINK_STATUS, &Success);
        if (!Success)
        {
            glGetProgramInfoLog(Shader, 1024, nullptr, InfoLog);
            CRESCENT_CORE_ERROR("[PROGRAM] LINKING: {}", Type);
            CRESCENT_CORE_WARN("[PROGRAM] : {}", InfoLog);
        }
    }
}
