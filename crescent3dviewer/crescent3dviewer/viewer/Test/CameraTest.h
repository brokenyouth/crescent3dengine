#pragma once
/*
#include "../GameFramework/CameraComponent.h"
#include "../Engine.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T>
inline T lerp(const T& a, const T& b, const float t)
{
    return (1.0f - t) * a + b * t;
}


class CameraTest
{
protected:
    Engine* GEngine = nullptr;
    Input* GInput = nullptr;
    Renderer* GRenderer = nullptr;
protected:
    glm::mat4 Projection;
    inline void SetProjection(const glm::mat4& InProjection) { Projection = InProjection; }
    glm::mat4 View;

    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 TargetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

    float FieldOfView;
    float AspectRatio;
    float NearClipPlane;
    float FarClipPlane;
    bool  Perspective;
    bool FirstMouse = false;

    float Speed = 20.f;
    float MouseSensitivity = 0.1f;
    float Yaw = -90.f;
    float Pitch = 0.0f;
    float TargetYaw = 0.0f;
    float TargetPitch = 0.0f;
    float Damping = 5.0f;

    float MouseX = 200;
    float MouseY = 300;
public:
    CameraTest();
    ~CameraTest() {}
    void Update(float DeltaTime);
public:
    inline void SetForwardVector(const glm::vec3& InForward) { Forward = InForward; }
    inline void SetUpVector(const glm::vec3& InUp) { Up = InUp; }
    inline void SetRightVector(const glm::vec3& InRight) { Right = InRight; }

    inline void SetFieldOfView(float InFieldOfView) { FieldOfView = InFieldOfView; }
    inline void SetAspectRatio(float InAspectRatio) { AspectRatio = InAspectRatio; }
    inline void SetNearClipPlane(float InNearClipPlane) { NearClipPlane = InNearClipPlane; }
    inline void SetFarClipPlane(float InFarClipPlane) { FarClipPlane = InFarClipPlane; }
    inline void SetCameraPerspective(bool bInPerspective) { Perspective = bInPerspective; UpdatePerspective(); }

    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();

protected:
    void UpdatePerspective();
    void UpdateViewMatrix();
};

CameraTest::CameraTest()
{
    GEngine = Engine::GetInstance();
    GRenderer = GEngine->GetRenderer().get();
    GInput = Input::GetInstance();
    SetAspectRatio(static_cast<float>(GRenderer->mViewportWidth) / GRenderer->mViewportHeight);
    SetFieldOfView(90.f);
    SetNearClipPlane(0.1f);
    SetFarClipPlane(9000.f);
    SetCameraPerspective(true);

    TargetPosition = Position;

    UpdatePerspective();
    //GEngine->GetGame()->SetCamera(this);
}

void CameraTest::Update(float DeltaTime)
{
    float Velocity = Speed * DeltaTime;

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

    /// 
    //slowly interpolate to target position each frame given some damping factor.
    // this gives smooth camera movement that fades out the closer we are to our target.
    Position = lerp(Position, TargetPosition, glm::clamp(DeltaTime * Damping, 0.f, 1.f));
    Yaw = lerp(Yaw, TargetYaw, glm::clamp(DeltaTime * Damping * 250.0f, 0.f, 1.f));
    Pitch = lerp(Pitch, TargetPitch, glm::clamp(DeltaTime * Damping * 250.0f, 0.f, 1.f));

    // calculate new cartesian basis vectors from yaw/pitch pair:
    glm::vec3 newForward;
    newForward.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    newForward.y = glm::sin(glm::radians(Pitch));
    newForward.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    Forward = glm::normalize(newForward);
    Right = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    Up = glm::cross(Right, Forward);

    /// 
    
    if (TargetYaw == 0.0f) TargetYaw = 0.01f;
    if (TargetPitch == 0.0f) TargetPitch = 0.01f;

    if (TargetPitch > 89.f)  TargetPitch = 89.f;
    if (TargetPitch < -89.f) TargetPitch = -89.f;

    if (GInput->IsKeyPressed("Forward"))
    {
        TargetPosition = TargetPosition + (Forward * Velocity);
    }
    if (GInput->IsKeyPressed("Backward"))
    {
        TargetPosition = TargetPosition - (Forward * Velocity);
    }
    if (GInput->IsKeyPressed("Right"))
    {
        TargetPosition = TargetPosition + (Right * Velocity);
    }
    if (GInput->IsKeyPressed("Left"))
    {
        TargetPosition = TargetPosition - (Right * Velocity);
    }
}
glm::mat4 CameraTest::GetProjectionMatrix()
{
    return Projection;
}
glm::mat4 CameraTest::GetViewMatrix()
{
    UpdateViewMatrix();
    return View;
}
void CameraTest::UpdatePerspective()
{
    Projection = glm::perspective(glm::radians(FieldOfView), AspectRatio, NearClipPlane, FarClipPlane);
}
void CameraTest::UpdateViewMatrix()
{
    View = glm::lookAt(Position, Position + Forward, Up);
}
*/