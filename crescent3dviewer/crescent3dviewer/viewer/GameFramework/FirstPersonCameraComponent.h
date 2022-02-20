#pragma once

#include "CameraComponent.h"

template <typename T>
inline T clerp(const T& a, const T& b, const float t)
{
	return (1.0f - t) * a + b * t;
}

/*
* Custom camera class to be attached to an actor
* Updates camera view based on mouse motion.
*/
class FirstPersonCameraComponent : public CameraComponent
{
private:
	float MouseSensitivity = 0.1f;
	float Yaw;
	float Pitch;
	float TargetYaw;
	float TargetPitch;
	bool FirstMouse;
	float Damping;

	float MouseX, MouseY;

	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
public:
	FirstPersonCameraComponent(Actor* InOwner, int InUpdateOrder);
	~FirstPersonCameraComponent();

	virtual void Update(float DeltaTime) override;
	virtual glm::mat4 GetViewMatrix() override;
private:
	virtual void UpdateViewMatrix() override;
	virtual void ProcessMouse();
};

