
#include "ParticlePool.h"
#include <assert.h>

// This pool constructer sets our particles to available
ParticlePool::ParticlePool()
{
	// The first particle is available
	firstAvailable = &particles[0];

	// Each particle points to the next one
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		particles[i].SetNext(&particles[i + 1]);
	}

	// The last particles points to nullptr indicating the end of the list
	particles[POOL_SIZE - 1].SetNext(nullptr);

}

void ParticlePool::Generate(iPoint pos, float speed, float angle, float start_radius, uint life)
{
	// Check if the pool is not full
	assert(firstAvailable != nullptr);

	// Remove it from the available list
	Particle* newParticle = firstAvailable;
	firstAvailable = newParticle->GetNext();

	newParticle->Init(pos, speed, angle, start_radius, life);
}

void ParticlePool::Update(float dt)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (particles[i].Animate(dt))
		{
			// Add this particle to the front of the list
			particles[i].SetNext(firstAvailable);
			firstAvailable = &particles[i];
		}
	}
}