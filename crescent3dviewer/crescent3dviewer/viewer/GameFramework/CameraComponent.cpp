#include "CameraComponent.h"
#include "../Renderer.h"
#include "../Input.h"
#include "../Engine.h"

CameraComponent::CameraComponent(Actor* InOwner, int InUpdateOrder)
	: Component(InOwner, InUpdateOrder)
{
	GEngine = Engine::GetInstance();
	GRenderer = GEngine->GetRenderer().get();
	GInput = Input::GetInstance();
	SetAspectRatio(static_cast<float>(GRenderer->mViewportWidth) / GRenderer->mViewportHeight);
	SetFieldOfView(68.f);
	SetNearClipPlane(0.1f);
	SetFarClipPlane(9000.f);
	SetCameraPerspective(true);

	Position = GetOwner()->GetActorPosition();
	TargetPosition = Position;

	Forward = GetOwner()->GetActorForward();
	Right = GetOwner()->GetActorRight();
	Up = GetOwner()->GetActorUp();
}

void CameraComponent::Update(float DeltaTime)
{
	AspectRatio = static_cast<float>(GRenderer->mViewportWidth) / GRenderer->mViewportHeight;
	UpdatePerspective();
}

glm::mat4 CameraComponent::GetProjectionMatrix()
{
	return Projection;
}

glm::mat4 CameraComponent::GetViewMatrix()
{
	UpdateViewMatrix();
	return View;
}

void CameraComponent::UpdatePerspective()
{
	if (Perspective)
	{
		glm::mat4 InProjection = glm::perspective(glm::radians(FieldOfView), AspectRatio, NearClipPlane, FarClipPlane);
		SetProjection(InProjection);
	}
	else
	{
		glm::mat4 InProjection = glm::ortho(-35.f, 35.f, -35.f, 35.f, NearClipPlane, FarClipPlane);
		SetProjection(InProjection);
	}
}

void CameraComponent::UpdateViewMatrix()
{
	const glm::vec3& Position = GetOwner()->GetActorPosition();
	View = glm::lookAt(Position, Position + Forward, Up);
}
