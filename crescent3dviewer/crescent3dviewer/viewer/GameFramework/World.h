#pragma once

#include "Actor.h"
#include "TestActor.h"

#include "../Model.h"
#include "../Timer.h"

#include <future>

class World
{

public:
	std::vector<Actor*> Actors;
	std::vector<Model*> Models;
	std::unique_ptr<Timer> Clock;
	std::string Name;
	bool Visible;

public:
	World();
	~World();

	void Initialize();
public:
	inline std::vector<Actor*> GetActors() const { return Actors; }
	inline std::vector<Model*> GetModels() const { return Models; }

	void Update(float DeltaTime);
	void Destroy();
	void AddActor(Actor* InChild);
	void RemoveActor(Actor* InChild);
	void AddModel(Model* InChild);
	void RemoveModel(Model* InChild);

	void SetVisible(bool bVisibilityFlag);

};

