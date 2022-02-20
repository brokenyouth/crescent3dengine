#include "FirstPersonCameraComponent.h"
#include "../Engine.h"

FirstPersonCameraComponent::FirstPersonCameraComponent(Actor* InOwner, int InUpdateOrder)
	: CameraComponent(InOwner, InUpdateOrder)
{
	FirstMouse = true;
	Damping = 5.f;
	MouseX = 200.0f;
	MouseY = 200.0f;
	Yaw = -90.0f;
	Pitch = 0.0f;
	TargetYaw = 0.0f;
	TargetPitch = 0.0f;

	float Speed = 20.f;
	float MouseSensitivity = 0.1f;

	GEngine->GetGame()->SetCamera(this);

}

FirstPersonCameraComponent::~FirstPersonCameraComponent()
{

}

void FirstPersonCameraComponent::Update(float DeltaTime)
{
	CameraComponent::Update(DeltaTime);

	ProcessMouse();

	Yaw = clerp(Yaw, TargetYaw, glm::clamp(DeltaTime * Damping * 250.0f, 0.f, 1.f));
	Pitch = clerp(Pitch, TargetPitch, glm::clamp(DeltaTime * Damping * 250.0f, 0.f, 1.f));

	// calculate new cartesian basis vectors from yaw/pitch pair:
	glm::vec3 NewForward(1.0f);
	NewForward.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
	NewForward.y = glm::sin(glm::radians(Pitch));
	NewForward.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
	Forward = glm::normalize(NewForward);
	Right = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	Up = glm::cross(Right, Forward);

	GetOwner()->SetActorForward(Forward);
	GetOwner()->SetActorRight(Right);
	GetOwner()->SetActorUp(Up);

	Position = GetOwner()->GetActorPosition();
	//CRESCENT_CORE_INFO("Yaw -> {}", Yaw);
	//CRESCENT_CORE_INFO("Pitch -> {}", Pitch);

}

glm::mat4 FirstPersonCameraComponent::GetViewMatrix() 
{
	UpdateViewMatrix();
	return View;
}

void FirstPersonCameraComponent::UpdateViewMatrix()
{
	View = glm::lookAt(Position, Position + Forward, Up);
}

void FirstPersonCameraComponent::ProcessMouse()
{
	auto [X, Y] = GInput->GetMouseXY();
	if (FirstMouse)
	{
		MouseX = X; MouseY = Y;
		FirstMouse = false;
	}
	float OffsetX = X - MouseX;
	float OffsetY = MouseY - Y;

	float MotionX = OffsetX * MouseSensitivity;
	float MotionY = OffsetY * MouseSensitivity;

	TargetYaw = glm::mod(TargetYaw + MotionX, 360.f);
	TargetPitch = TargetPitch + MotionY;

	MouseX = X;
	MouseY = Y;

	if (TargetYaw == 0.0f) TargetYaw = 0.01f;
	if (TargetPitch == 0.0f) TargetPitch = 0.01f;

	if (TargetPitch > 89.f)  TargetPitch = 89.f;
	if (TargetPitch < -89.f) TargetPitch = -89.f;
}
