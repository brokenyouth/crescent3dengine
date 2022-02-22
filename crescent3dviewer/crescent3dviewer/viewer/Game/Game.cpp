#include "Game.h"

#include "../Engine.h"
#include "../GameFramework/TestActor.h"
#include "../GameFramework/CameraComponent.h"
#include "../ResourceManager.h"
#include "../RenderCommand.h"

std::mutex sResMutex;

Game::Game()
{

}

Game::~Game()
{
	delete TActor;
	delete DummyActor;
	delete Camera;
}


void Game::SetCamera(CameraComponent* InCamera)
{
	Camera = InCamera;
}

void Game::PrepareResources(std::vector<std::string> Paths)
{
	std::vector<std::future<void>> ResFutures;
	for (auto i = 0; i < Paths.size(); ++i)
	{
		auto j = std::async([&Paths, &ResFutures, i]() {
			Engine::GetInstance()->LoadResource(EResourceType::MODEL, Paths[i]);
			});
		ResFutures.push_back(std::move(j));
	}
}

void Game::Initialize()
{
	std::vector<std::string> ModelsPath = {};
	ModelsPath.push_back("./assets/maps/cs_1943/cs_1943.obj");
	//ModelsPath.push_back("./assets/old/Sponza/Sponza.gltf");
	//ModelsPath.push_back("./assets/SciFiHelmet/SciFiHelmet.gltf");
	//ModelsPath.push_back("./assets/t/scene.gltf");

	PrepareResources(std::ref(ModelsPath));

	WorldMap = std::make_shared<World>();

	TActor = new TestActor();
	WorldMap->AddActor(TActor);

	DummyActor = new Actor();
}

void Game::Input()
{

}

void Game::Update(float DeltaTime)
{
	Engine* GEngine = Engine::GetInstance();
	for (Actor* ChildActor : WorldMap->GetActors())
	{
		ChildActor->Tick(DeltaTime);
		GEngine->GetRenderer()->Push(ChildActor);
	}

}

void Game::Render()
{
	Shader* DefaultShader = ResourceManager::GetInstance()->GetShader("default");
	DefaultShader->Bind();

	DefaultShader->SetUniformMat4("ProjectionMatrix", Camera->GetProjectionMatrix());
	DefaultShader->SetUniformMat4("ViewMatrix", Camera->GetViewMatrix());

	DefaultShader->Unbind();
	
}

void Game::SetResourceAvailable(Model* InResource)
{
	WorldMap->AddModel(InResource);
	DummyActor->SetModel(InResource);
	WorldMap->AddActor(DummyActor);
}
