#include "Engine.h"
#include "Input.h"

static std::mutex sMutex;
Engine* Engine::sInstance = nullptr;

Engine::Engine() 
{
	bInitialized = false;
	bLoadingResource = true;
}

Engine::~Engine()
{

}

Engine* Engine::GetInstance()
{
	if (sInstance)
		return sInstance;
	else
	{
		sInstance = new Engine();
		return sInstance;
	}
}

Game* Engine::GetGame() const
{
	return mGame;
}

void Engine::Initialize(int Width, int Height, const std::string& Name)
{
	WindowInfo WndInfo = {
		Width,
		Height,
		Name.c_str()
	};
	Logger::Initialize();
	CRESCENT_CORE_INFO("Initializing engine...");
	mWindow = std::make_shared<Window>();
	mWindow->Initialize(WndInfo);
	mRenderer = std::make_shared<Renderer>();
	mRenderer->Initialize();
	mRenderer->SetViewport(0, 0, Width, Height);
	mTimer = std::make_shared<Timer>();
	ResourceManager::GetInstance();
	Input::GetInstance();

	mGame = new Game();
}

void Engine::Release()
{
	delete mGame;
	mGame = nullptr;

	ResourceManager::GetInstance()->Release();
	Input::GetInstance()->Release();

	mWindow->Release();
	delete sInstance;
	sInstance = nullptr;

	CRESCENT_CORE_INFO("Engine released.");
}

void Engine::Run()

{
	ResourceManager::GetInstance()->LoadShader("default", "./shaders/default_vs.glsl", "./shaders/default_fs.glsl");
	Shader* DefaultShader = ResourceManager::GetInstance()->GetShader("default");
	DefaultShader->CreateUniform("ProjectionMatrix");
	DefaultShader->CreateUniform("ViewMatrix");
	DefaultShader->CreateUniform("ModelMatrix");

	ResourceManager::GetInstance()->LoadShader("skyshader", "./shaders/skybox_vs.glsl", "./shaders/skybox_fs.glsl");
	Shader* SkyShader = ResourceManager::GetInstance()->GetShader("skyshader");
	SkyShader->CreateUniform("ProjectionMatrix");
	SkyShader->CreateUniform("ViewMatrix");

	mGame->Initialize();

	while (!mWindow->WindowShouldClose())
	{
		float DeltaTime = mTimer->GetDeltaTime();
		mTimer->Reset();
		mWindow->PollEvents();

		Input();
		Update(DeltaTime);
		Render();

		mWindow->SwapBuffers();
	}

	Release();
}

void Engine::LoadResource(EResourceType InType, std::string Path)
{
	if (InType == EResourceType::MODEL)
	{
		auto Fu = std::async(std::launch::async, LoadModel, std::ref(mModelQueue), Path);
		mFutures.push_back(std::move(Fu));
	}
}

Model* Engine::GetModel(const std::string& Path)
{
	auto Iterator = mModels.find(Path);
	if (Iterator != mModels.end())
	{
		return Iterator->second.get();
	}
	return nullptr;
}

void Engine::LoadModel(std::queue<std::shared_ptr<Model>>& InContainer, std::string Path)
{
	std::lock_guard<std::mutex> Lock(sMutex);
	std::shared_ptr<Model> LoadedModel = std::make_shared<Model>(Path);
	InContainer.push(LoadedModel);
}

void Engine::Input()
{
	mGame->Input();
}

void Engine::Update(float DeltaTime)
{
	auto Size = mModelQueue.size();
	for (auto i = 0; i < Size; ++i)
	{
		std::shared_ptr<Model> OutModel = mModelQueue.front();
		mModelQueue.pop();
		OutModel->PrepareModel();
		mModels[OutModel->GetModelPath()] = OutModel;

		// inform client(game, sandbox, etc.) that this resource is ready to be work with.
		mGame->SetResourceAvailable(OutModel.get());
	}

	mGame->Update(DeltaTime);
}

void Engine::Render()
{
	mRenderer->Flush();
	mGame->Render();
}
