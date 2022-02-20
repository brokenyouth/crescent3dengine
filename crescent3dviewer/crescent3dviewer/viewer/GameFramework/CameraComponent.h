#pragma once

#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer;
class Input;
class Engine;

class CameraComponent : public Component
{
protected:
    Engine* GEngine = nullptr;
    Input* GInput = nullptr;
    Renderer* GRenderer = nullptr;
protected:
    glm::mat4 Projection;
    inline void SetProjection(const glm::mat4& InProjection) { Projection = InProjection; }
    glm::mat4 View;

    glm::vec3 Position;
    glm::vec3 TargetPosition;
    glm::vec3 Forward;
    glm::vec3 Up;
    glm::vec3 Right;

    float FieldOfView;
    float AspectRatio;
    float NearClipPlane;
    float FarClipPlane;
    bool  Perspective;

public:
    CameraComponent(Actor* InOwner, int InUpdateOrder);
    virtual ~CameraComponent() {}
    virtual void Update(float DeltaTime) override;

public:
    inline void SetForwardVector(const glm::vec3& InForward) { Forward = InForward; }
    inline void SetUpVector(const glm::vec3& InUp) { Up = InUp; }
    inline void SetRightVector(const glm::vec3& InRight) { Right = InRight; }

    inline void SetFieldOfView(float InFieldOfView) { FieldOfView = InFieldOfView; }
    inline void SetAspectRatio(float InAspectRatio) { AspectRatio = InAspectRatio; }
    inline void SetNearClipPlane(float InNearClipPlane) { NearClipPlane = InNearClipPlane; }
    inline void SetFarClipPlane(float InFarClipPlane) { FarClipPlane = InFarClipPlane; }
    inline void SetCameraPerspective(bool bInPerspective) { Perspective = bInPerspective; UpdatePerspective(); }

    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::mat4 GetViewMatrix();

protected:
    virtual void UpdatePerspective();
    virtual void UpdateViewMatrix();
};

