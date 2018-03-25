
#include "p2Log.h"
#include "j1ParticleSystem.h"
#include "j1App.h"
#include "j1Textures.h"



j1ParticleSystem::j1ParticleSystem() : j1Module()
{
	name = "psystem";
}

j1ParticleSystem::~j1ParticleSystem()
{
	
}

bool j1ParticleSystem::Awake(pugi::xml_node &)
{
	return true;
}

bool j1ParticleSystem::Start()
{
	particleAtlas = App->tex->Load("textures/particle.png");

	return true;
}

// TODO: need to figure out if only call update or also preupdate.
// This will depend on the way the emitter is organized in terms of
// drawing and updating the particles with one or more methods.

// if emitters have two separe methods for update and draw we would call
// update on preUpdate and draw on Update

bool j1ParticleSystem::PreUpdate()
{

	return true;
}

bool j1ParticleSystem::Update(float dt)
{
	for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters.at(i) != nullptr)
			emitters[i]->Update(dt);
	}

	return true;
}

bool j1ParticleSystem::PostUpdate()
{
	for (int i = emitters.size() - 1; i >= 0 && !emitters.empty(); --i)
	{
		if (emitters[i]->to_destroy)
		{
			delete(emitters[i]);
			emitters[i] = nullptr;

			emitters.erase(emitters.cbegin() + i);
		}
	}

	emitters.shrink_to_fit();

	return true;
}

// TODO: check inputcombo cleanup
bool j1ParticleSystem::CleanUp()
{
	LOG("Freeing emitters from the system.");

	std::vector<Emitter*>::const_iterator itEmitter = this->emitters.begin();

	while (itEmitter!= this->emitters.end())
	{
		delete *itEmitter;
		itEmitter++;
	}

	emitters.clear();

	/*for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters[i] != nullptr)
		{
			delete emitters[i];
			emitters[i] = nullptr;

			emitters.erase(emitters.cbegin() + i);
		}
	}*/

	App->tex->UnLoad(particleAtlas);
	
	return true;
}

// TODO: we should be able to add different types of emitters.
// For now, we wil stay with one to make sure it works. Then we
// can add more.

Emitter * j1ParticleSystem::AddEmiter(iPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize)
{
	Emitter* tmp_emitter = new Emitter(pos, emitNumber, emitVariance, maxParticleLife, angleRange, maxSpeed, maxSize);
	emitters.push_back(tmp_emitter);
	
	return tmp_emitter;
}

bool j1ParticleSystem::RemoveEmitter(Emitter & emitter)
{
	for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) == &emitter) 
		{
			emitters[i]->to_destroy = true;
			return true;
		}
	}

	return false;
}

bool j1ParticleSystem::RemoveAllEmitters()
{
	bool ret = false;

	for (uint i = 0; i < emitters.size(); i++) 
	{
		if (emitters.at(i) != nullptr) emitters[i]->to_destroy = true;
		ret = true;
	}

	return ret;
}
 
SDL_Texture* j1ParticleSystem::GetParticleAtlas() const
{
	return particleAtlas;
}