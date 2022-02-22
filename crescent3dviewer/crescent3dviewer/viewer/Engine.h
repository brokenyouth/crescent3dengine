#pragma once

#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "Timer.h"
#include "Skybox.h"
#include "Game/Game.h"

#include "Logger.h"

#include <future>
#include <unordered_map>
#include <queue>

enum EResourceType
{
	MODEL,
	SOUND,
	SHADER,
	TEXTURE
};

class Engine
{
private:
	static Engine* sInstance;
	bool bInitialized;

	bool bLoadingResource;

	std::shared_ptr<Window> mWindow;
	std::shared_ptr<Renderer> mRenderer;
	std::shared_ptr<Timer> mTimer;

	std::queue<std::shared_ptr<Model>> mModelQueue = {};
	std::unordered_map<std::string, std::shared_ptr<Model>> mModels = {};
	std::vector<std::future<void>> mFutures = {};

	std::shared_ptr<Skybox> mSkybox;
	Game* mGame = nullptr;

private:
	Engine();
	~Engine();

public:
	static Engine* GetInstance();

	void Initialize(int Width, int Height, const std::string& Name);
	void Release();
	void Run();

	void LoadResource(EResourceType, std::string Path);

	Model* GetModel(const std::string& Path);
	Model* GetPrimitive();

	Game* GetGame() const;
	inline std::shared_ptr<Renderer>& GetRenderer() { return mRenderer; }
	inline std::shared_ptr<Window>& GetWindow() { return mWindow; }
private:
	void Input();
	void Update(float DeltaTime);
	void Render();

	static void LoadModel(std::queue<std::shared_ptr<Model>>& InContainer, std::string Path);

};

