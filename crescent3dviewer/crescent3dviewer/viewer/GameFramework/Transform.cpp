#include "Transform.h"

Transform::Transform()
{
	Translation = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::SetTranslation(const glm::vec3& NewTranslation)
{
	Translation = NewTranslation;
}

void Transform::SetRotation(const glm::quat& NewRotation)
{
	Rotation = NewRotation;
}

void Transform::SetScale(const glm::vec3& NewScale)
{
	Scale = NewScale;
}

const glm::vec3& Transform::GetTranslation() const
{
	return Translation;
}

const glm::quat& Transform::GetRotation() const
{
	return Rotation;
}

const glm::vec3& Transform::GetScale() const
{
	return Scale;
}
