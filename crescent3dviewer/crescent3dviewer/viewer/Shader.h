#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <GL/glew.h>

class Shader
{
private:
    GLuint mProgramId;
    GLuint mVertexShaderId;
    GLuint mFragmentShaderId;
    std::map<std::string, int> mUniformsMap;
public:
    Shader(const char* VertexPath, const char* FragmentPath);
    virtual ~Shader();
public:
    void Use();
    void Bind();
    void Unbind();
    void Release();
    void CreateUniform(const std::string& Name);
    void SetUniformMat4(const std::string& Name, const glm::mat4& Value);
    void SetUniformInt(const std::string& Name, uint32_t Value);
    void SetUniformVec3(const std::string& Name, const glm::vec3& Value);
    void SetUniformFloat(const std::string& Name, float Value);
    std::string LoadShaderFromFile(const char* ShaderPath) const;
    std::string GetShaderName(const char* ShaderPath) const;
    void CheckCompilationErrors(GLuint Shader, const std::string& Type, const std::string& ShaderName);
};

typedef std::shared_ptr<Shader> ShaderPtr;