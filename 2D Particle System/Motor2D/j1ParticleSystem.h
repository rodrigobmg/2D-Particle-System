#ifndef __J1_PARTICLE_SYSTEM_H__
#define __J1_PARTICLE_SYSTEM_H__

#include "p2Point.h"
#include "j1Module.h"
#include "Emitter.h"
#include <list>

class Emitter;
struct SDL_Texture;
struct SDL_Rect;

class j1ParticleSystem : public j1Module
{
private:

	std::list<Emitter*> emittersList;
	SDL_Texture* particleAtlas = nullptr;
	
public:

	j1ParticleSystem();

	// Destructor
	virtual ~j1ParticleSystem();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Emitter methods
	Emitter* AddEmiter(fPoint pos, uint emitNumber, uint emitVariance, uint maxParticleLife, fPoint angleRange, float maxSpeed, float maxSize, SDL_Rect textureRect, double lifeTime = -1.0f);
	bool RemoveEmitter(Emitter& emitter);
	bool RemoveAllEmitters();
	SDL_Texture* GetParticleAtlas() const;
};

#endif