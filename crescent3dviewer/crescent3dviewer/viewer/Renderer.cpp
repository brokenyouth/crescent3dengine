#include "Renderer.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "RenderCommand.h"
#include <GL/glew.h>

#include "GameFramework/CameraComponent.h"
#include "GameFramework/ModelComponent.h"


Renderer::Renderer()
{
	bInitialized = false;
}

void Renderer::Initialize()
{
	CRESCENT_CORE_INFO("Initializing OpenGL renderer. ");

	if (bInitialized)
	{
		CRESCENT_CORE_INFO("OpenGL renderer already initialized. Aborting initialization call. ");
		return;
	}

	CRESCENT_CORE_INFO("OpenGL version: {} ", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bInitialized = true;
	CRESCENT_CORE_INFO("Initialized OpenGL renderer. ");

}

void Renderer::Release()
{
	if (bInitialized)
	{
		bInitialized = false;
		CRESCENT_CORE_INFO("OpenGL renderer released. ");
	}
}

void Renderer::Push(Actor* InActor)
{
	mRenderQueue.push(InActor);
}

void Renderer::Flush()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	int Size = mRenderQueue.size();
	for (auto i = 0; i < Size; i++)
	{
		Actor* CurrentActor = mRenderQueue.front();
		mRenderQueue.pop();
		Model* CurrentModel = static_cast<ModelComponent*>(CurrentActor->GetModelComponent())->GetModel();
		Shader* CurrentShader = static_cast<ModelComponent*>(CurrentActor->GetModelComponent())->GetShader();

		if (CurrentModel && CurrentShader)
		{
			for (auto& Mesh : CurrentModel->GetMeshes())
			{
				RenderMesh RM = RenderMesh(CurrentShader, Mesh.get());
				RM.Execute(CurrentActor->GetActorWorldTransform());
			}
		}
	}
}

void Renderer::SetViewport(int X, int Y, int Width, int Height)
{
	mX = X;
	mY = Y;
	mViewportWidth = Width;
	mViewportHeight = Height;
	glViewport(mX, mY, mViewportWidth, mViewportHeight);
}

void Renderer::SetCamera(CameraComponent* InCamera)
{
	Camera = InCamera;
}
