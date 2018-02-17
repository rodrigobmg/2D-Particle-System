#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		float randomSpeed = rand() % (50 - 150 + 1) + 50;
		float randomAngle = rand() % (0 - 360 + 1) + 0;;
		int randomLife = rand() % (0 - 150 + 1) + 0;

		testParticle[i] = new Particle({ 500, 500 }, randomSpeed, randomAngle, randomLife);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	for (int i = 0; i < 100; i++)
	{
		if (!testParticle[i]->IsDead())
			testParticle[i]->Update(dt);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	for (int i = 0; i < 50; i++)
	{
		delete testParticle[i];
	}

	return true;
}