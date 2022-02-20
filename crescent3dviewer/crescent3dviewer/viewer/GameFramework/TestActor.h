#pragma once
#include "Actor.h"
#include "MovementComponent.h"
#include "FirstPersonCameraComponent.h"

class TestActor : public Actor
{
private:
	int CurrentUpdateOrder = 0;
public:
	TestActor();
	virtual ~TestActor();

	/* called every frame to update actor */
	virtual void Tick(float DeltaTime) override;
};

