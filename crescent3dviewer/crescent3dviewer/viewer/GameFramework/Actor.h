#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Transform.h"
#include "../Model.h"

class Component;
class Game;

/**
* Base class for an object that can be spawned in a world.
*/
class Actor
{
protected:
	std::string mName;
	Component* mModelComponent; // This component is necessary that's why it is set as a member
	std::vector<Component*> mComponents;
	Transform mTransform;
	glm::mat4 mWorldTransform;

	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	bool bVisible = true;

public:
	Actor();
	virtual ~Actor();

	/* called every frame to update actor */
	virtual void Tick(float DeltaTime);
	/* called when actor must be destroyed */
	virtual void Destroy();

public:
	virtual void AddComponent(Component* InComponent);
	virtual void RemoveComponent(Component* InComponent);

	virtual void SetVisible(bool bVisibilityFlag);
	virtual bool IsVisible() const;

private:
	void CalculateWorldTransform();

public:
	void SetActorPosition(const glm::vec3& InPosition);
	void SetActorForward(const glm::vec3& InForward);
	void SetActorRight(const glm::vec3& InRight);
	void SetActorUp(const glm::vec3& InUp);

	const glm::vec3& GetActorPosition() const;
	const glm::mat4& GetActorWorldTransform();
	const glm::vec3& GetActorForward() const;
	const glm::vec3& GetActorRight() const;
	const glm::vec3& GetActorUp() const;

	void SetModel(Model* InModel);
	Component* GetModelComponent() const;
};

typedef std::shared_ptr<Actor> ActorPtr;