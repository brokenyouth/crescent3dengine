#include "World.h"

World::World()
{
	Name = "World";
	Clock = std::make_unique<Timer>();
}

World::~World()
{

}

void World::Initialize()
{
}

void World::Update(float DeltaTime)
{
    for (auto Child : Actors)
    {
        Child->Tick(DeltaTime);
    }
}

void World::Destroy()
{
	for (auto Child : Actors)
	{
		Child->Destroy();
	}
}

// Could use template here to compress code of Actor/Model
// But let's avoid that for now.
void World::AddActor(Actor* InChild)
{
    Actors.push_back(InChild);
}

void World::RemoveActor(Actor* InChild)
{

    for (auto Iterator = Actors.begin(); Iterator != Actors.end(); )
    {
        if ((*Iterator) == InChild)
        {
            Actors.erase(Iterator);

        }
        else
        {
            Iterator++;
        }
    }
}

void World::AddModel(Model* InChild)
{
    Models.push_back(InChild);
}

void World::RemoveModel(Model* InChild)
{
    for (auto Iterator = Models.begin(); Iterator != Models.end(); )
    {
        if ((*Iterator)->GetModelPath() == InChild->GetModelPath())
        {
            Models.erase(Iterator);
        }
        else
        {
            Iterator++;
        }
    }
}


void World::SetVisible(bool bVisibilityFlag)
{
	Visible = bVisibilityFlag;
}



