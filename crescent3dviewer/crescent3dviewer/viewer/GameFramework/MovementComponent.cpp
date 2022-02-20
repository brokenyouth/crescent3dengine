#include "MovementComponent.h"

template <typename T>
inline T lerp(const T& a, const T& b, const float t)
{
	return (1.0f - t) * a + b * t;
}

MovementComponent::MovementComponent(Actor* InOwner, int InUpdateOrder = 10) :
	Component(InOwner, InUpdateOrder)
{
	Input = Input::GetInstance();
	Position = GetOwner()->GetActorPosition();
	TargetPosition = Position;
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(float DeltaTime)
{
	glm::vec3 Forward = GetOwner()->GetActorForward();
	glm::vec3 Right = GetOwner()->GetActorRight();

	float Velocity = Acceleration * DeltaTime;

	if (Input->IsKeyPressed("Forward"))
	{
		TargetPosition = TargetPosition + (Forward * Velocity);
	}
	if (Input->IsKeyPressed("Backward"))
	{
		TargetPosition = TargetPosition - (Forward * Velocity);
	}
	if (Input->IsKeyPressed("Right"))
	{
		TargetPosition = TargetPosition + (Right * Velocity);
	}
	if (Input->IsKeyPressed("Left"))
	{
		TargetPosition = TargetPosition - (Right * Velocity);
	}

	Position = lerp(Position, TargetPosition, glm::clamp(DeltaTime * 5.0f, 0.f, 1.f));
	GetOwner()->SetActorPosition(Position);

}
