#ifndef __J1_PARTICLE_SYSTEM_H__
#define __J1_PARTICLE_SYSTEM_H__

#include "p2Point.h"
#include "j1Module.h"
#include "Emitter.h"
#include <vector>

class Emitter;
struct SDL_Texture;

class j1ParticleSystem : public j1Module
{
private:

	std::vector<Emitter*> emitters;
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

	Emitter* AddEmiter();
	bool RemoveEmitter(Emitter& emitter);
	bool RemoveAllEmitters();
	const SDL_Texture* GetParticleAtlas() const;
};

#endif