#pragma once

#include "Shader.h"

#include <unordered_map>
#include <string>
#include <vector>

class ShaderManager
{
	static ShaderManager* sInstance;
private:
	std::unordered_map<std::string, Shader*> mShaders = {};

private:
	ShaderManager();
	~ShaderManager();
	void Initialize();

public:
	void Release();

	static ShaderManager* GetInstance();
	static ShaderManager* Get();

	Shader* GetShader(std::string& InShaderName);

};

