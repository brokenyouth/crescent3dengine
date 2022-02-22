#pragma once

#include "Component.h"
#include "../Model.h"
#include "../ShaderManager.h"

class ModelComponent : public Component
{
private:
	Model* mModel;
	Shader* mShader;

public:
	ModelComponent(Actor* InOwner, int InUpdateOrder = 5);
	~ModelComponent();

	Model* GetModel() const;
	void SetModel(Model* InModel);

	Shader* GetShader() const;
	void SetShader(Shader* InShader);
};

