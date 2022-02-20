#pragma once

#include "Mesh.h"
#include "Shader.h"

class RenderCommand
{
public:
	virtual void Execute(glm::mat4 Model) = 0;
	virtual ~RenderCommand() {}
};

class RenderMesh : public RenderCommand
{
private:
	Mesh* mMesh;
	Shader* mShader;

public:
	RenderMesh(Shader* Shader, Mesh* Mesh);
	virtual ~RenderMesh() {}
	virtual void Execute(glm::mat4 Model) override;
};