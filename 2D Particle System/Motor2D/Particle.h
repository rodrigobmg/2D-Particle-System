#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Particle
{
	private:

	uint life = 0, startLife = 0;

	struct Vortex
	{
		fPoint pos = { 250.0f, 200.0f };
		float speed = 25.0f;
		float scale = 30.0f;
	} vortex;

	union ParticleInfo
	{
		/* This struct holds the state of the particle when 
		   it's being update (it's still alive).*/
		struct ParticleState
		{
			fPoint pos;
			fPoint vel;
			float currentSize, startSize, endSize;
			float ageRatio;
			float angle;
			double startRotSpeed;
			double currentRotSpeed;
			SDL_Rect pRect;
			SDL_Rect rectSize;
			SDL_Color startColor;
			SDL_Color endColor;
			SDL_BlendMode blendMode;
			float t;

			ParticleState() {}

		} pLive;

		/* If the particle is dead, then the 'next' member comes 
		   into play and the struct it's not used. This pointer
		   called 'next' holds a pointer to the next available 
		   particle after this one. */
		Particle* next;

		ParticleInfo() {}
	} pState;

	public:

	Particle();

	// Initializes new generated particle
	void Init(fPoint pos, float speed, float angle, double rotSpeed, float startSize, float endSize, uint life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode);

	// Generic methods
	void Update(float dt);
	void Draw();
	bool IsAlive();

	// Particle pointer methods
	Particle* GetNext();
	void SetNext(Particle* next);

	// Given two colors interpolates linearly over time and returns the resulting color
	SDL_Color RgbInterpolation(SDL_Color startColor, SDL_Color endColor, float timeStep);

	// Vortex methods
	void AddVortex(fPoint pos, float speed, float scale);
	void CalculatePosFromVortex(float dt);
};

#endif