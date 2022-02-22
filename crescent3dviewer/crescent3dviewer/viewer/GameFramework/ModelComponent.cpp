#include "ModelComponent.h"

ModelComponent::ModelComponent(Actor* InOwner, int InUpdateOrder) 
    : Component(InOwner, InUpdateOrder)
{
    std::string ShaderName("default");
    mShader = ShaderManager::Get()->GetShader(ShaderName);
}

ModelComponent::~ModelComponent()
{
}

Model* ModelComponent::GetModel() const
{
    return mModel;
}

void ModelComponent::SetModel(Model* InModel)
{
    mModel = InModel;
}

Shader* ModelComponent::GetShader() const
{
    return mShader;
}

void ModelComponent::SetShader(Shader* InShader)
{
    mShader = InShader;
}
