#include "Component.h"

Component::Component(Actor* InOwner, int InUpdateOrder)
{
    Owner = InOwner;
    UpdateOrder = InUpdateOrder;
    
    if (Owner)
    {
        Owner->AddComponent(this);
    }
}

Component::~Component()
{
    if (Owner)
    {
        Owner->RemoveComponent(this);
    }
}

void Component::Update(float DeltaTime)
{
}

Actor* Component::GetOwner() const
{
    return Owner;
}

int Component::GetUpdateOrder() const
{
    return UpdateOrder;
}
