#pragma once

#include "Component.h"
#include "../Input.h"

class MovementComponent : public Component
{
public:
	Input* Input;
protected:
	float MaxSpeed = 260.0f;
	float ForwardSpeed = 0.0f;
	float SideSpeed = 0.0f;
	float Acceleration = 10.0f;

	glm::vec3 Position;
	glm::vec3 TargetPosition;
public:
	MovementComponent(Actor* InOwner, int InUpdateOrder);
	virtual ~MovementComponent();

	virtual void Update(float DeltaTime) override;
};

