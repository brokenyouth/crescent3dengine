#include "Actor.h"
#include "Component.h"
#include "ModelComponent.h"

#include <algorithm>
#include <glm/gtx/quaternion.hpp>

Actor::Actor()
{
	mName = "Actor";
	bVisible = true;

	SetActorPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	SetActorForward(glm::vec3(0.0f, 0.0f, -1.0f));
	SetActorRight(glm::vec3(1.0f, 0.0f, 0.0f));
	SetActorUp(glm::vec3(0.0f, 1.0f, 0.0f));

	mModelComponent = new ModelComponent(this);
}


Actor::~Actor()
{
	delete mModelComponent;
}

void Actor::Tick(float DeltaTime)
{
	for (Component* Comp : mComponents)
	{
		Comp->Update(DeltaTime);
	}
}

void Actor::Destroy()
{

}

void Actor::AddComponent(Component* InComponent)
{
	mComponents.push_back(InComponent);
	// Using lambda expressions in C++11
	std::sort(mComponents.begin(), mComponents.end(), [](const Component* Lhs, const Component* Rhs) {
		return Lhs->GetUpdateOrder() < Rhs->GetUpdateOrder();
		});
}

void Actor::RemoveComponent(Component* InComponent)
{
	auto Iterator = std::find(mComponents.begin(), mComponents.end(), InComponent);
	if (Iterator != mComponents.end())
	{
		mComponents.erase(Iterator);
	}
}

void Actor::SetVisible(bool bVisibilityFlag)
{
	if (bVisible == bVisibilityFlag) return;

	bVisible = bVisibilityFlag;
	// call set visible on children
}


bool Actor::IsVisible() const
{
	return bVisible;
}

void Actor::CalculateWorldTransform()
{
	// In this order:
	// Scale -> Rotation -> Translation
	mWorldTransform = glm::mat4(1.0f);
	mWorldTransform = glm::scale(mWorldTransform, mTransform.GetScale());
	mWorldTransform = mWorldTransform * glm::mat4_cast(mTransform.GetRotation());
	mWorldTransform = glm::translate(mWorldTransform, mTransform.GetTranslation());

}

void Actor::SetActorPosition(const glm::vec3& InPosition)
{
	mTransform.SetTranslation(InPosition);
}

void Actor::SetActorForward(const glm::vec3& InForward)
{
	Forward = InForward;
}

void Actor::SetActorRight(const glm::vec3& InRight)
{
	Right = InRight;
}

void Actor::SetActorUp(const glm::vec3& InUp)
{
	Up = InUp;
}

const glm::vec3& Actor::GetActorPosition() const
{
	glm::vec3 Position = mTransform.GetTranslation();
	return Position;
}

const glm::mat4& Actor::GetActorWorldTransform()
{
	CalculateWorldTransform();
	return mWorldTransform;
}

const glm::vec3& Actor::GetActorForward() const
{
	return Forward;
}

const glm::vec3& Actor::GetActorRight() const
{
	return Right;
}

const glm::vec3& Actor::GetActorUp() const
{
	return Up;
}

void Actor::SetModel(Model* InModel)
{
	static_cast<ModelComponent*>(mModelComponent)->SetModel(InModel);
}

Component* Actor::GetModelComponent() const
{
	return mModelComponent;
}
