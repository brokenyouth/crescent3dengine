#pragma once

#include "../GameFramework/World.h"
#include "../Model.h"

class CameraComponent;

class Game
{
public:
	friend class CameraComponent;

private:
	std::shared_ptr<World> WorldMap;
	std::shared_ptr<Model> TestModel;

	CameraComponent* Camera = nullptr;
	Actor* TActor = nullptr;
	Actor* DummyActor = nullptr;

public:
	Game();
	~Game();

public:
	void SetCamera(CameraComponent* InCamera);
	inline CameraComponent* GetCamera() const { return Camera; }

	void Initialize();
	void Input();
	void Update(float DeltaTime);
	void Render();

	void SetResourceAvailable(Model* InResource);

	static void PrepareResources(std::vector<std::string> Paths);
};

