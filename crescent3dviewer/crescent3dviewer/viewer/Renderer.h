#pragma once

#include "GameFramework/World.h"
#include "Model.h"

#include <queue>

class CameraComponent;
class ModelComponent;

class Renderer
{
public:
	friend class CameraComponent;
	friend class ModelComponent;
private:
	bool bInitialized = false;
	int mX;
	int mY;
	int mViewportWidth;
	int mViewportHeight;

	std::queue<Actor*> mRenderQueue = {};
	CameraComponent* Camera = nullptr;
public:
	Renderer();
	virtual ~Renderer() {}
public:
	void Initialize();
	void Release();

	void Push(Actor* InActor);
public:
	void Flush();
	void SetViewport(int X, int Y, int Width, int Height);
	void SetCamera(CameraComponent* InCamera);
	inline CameraComponent* GetCamera() const { return Camera; }
	inline glm::mat4 GetCameraProjectionMatrix() const { return Camera->GetProjectionMatrix(); }
	inline glm::mat4 GetCameraViewMatrix() const { return Camera->GetViewMatrix(); }

};

