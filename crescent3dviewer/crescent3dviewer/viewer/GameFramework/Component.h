#pragma once

#include "Actor.h"

class Component
{
protected:
	Actor* Owner = nullptr;
	int UpdateOrder;

public:
	Component(Actor* InOwner, int InUpdateOrder);
	virtual ~Component();

	virtual void Update(float DeltaTime);
	Actor* GetOwner() const;
	int GetUpdateOrder() const;
};

