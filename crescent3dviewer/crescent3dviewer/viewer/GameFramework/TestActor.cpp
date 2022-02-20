#include "TestActor.h"
#include "../Logger.h"

TestActor::TestActor()
{
	AddComponent(new MovementComponent(this, 1));
	AddComponent(new FirstPersonCameraComponent(this, 2));
}

TestActor::~TestActor()
{
}

void TestActor::Tick(float DeltaTime)
{
	Actor::Tick(DeltaTime);
	//auto Pos = GetActorPosition();
	//CRESCENT_CORE_INFO("{} - {} - {}", Pos.x, Pos.y, Pos.z);
}
