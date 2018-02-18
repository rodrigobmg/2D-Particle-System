#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "p2Point.h"

#define PI 3.14159265359f
#define DEG_TO_RAD(a) a * PI / 180.0f
#define RAD_TO_DEG(a) a * 180.0f / PI

class Particle
{
	private:

	iPoint pos = { 0, 0 };
	iPoint vel = { 0, 0 };
	uint life = 0;
	uint start_life = 0;
	bool dead = false;
	float radius = 0.0f;
	float ageRatio = 0.0f;
	int alpha = 0;
	float start_radius = 0.0f;
	float angle = 0.0f;

	public:

	Particle();
	void Init(iPoint pos, float speed, float angle, float start_radius, uint life);

	void Move(float dt);
	void Draw();
	void Update(float dt);

	bool IsDead();
};

#endif