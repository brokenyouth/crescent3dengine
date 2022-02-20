#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

class Transform
{
private:
	glm::vec3 Translation;
	glm::quat Rotation;
	glm::vec3 Scale;

public:
	Transform();
	~Transform();

public:
	void SetTranslation(const glm::vec3& NewTranslation);
	void SetRotation(const glm::quat& NewRotation);
	void SetScale(const glm::vec3& NewScale);

	const glm::vec3& GetTranslation() const;
	const glm::quat& GetRotation() const;
	const glm::vec3& GetScale() const;
};

