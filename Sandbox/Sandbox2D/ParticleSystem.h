#pragma once

#include "RKEngine.h"

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
	float Rotation = 0.0f;
	float RotationStart = 0.0f;
	float RotationEnd = 0.0f;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void Emit(const ParticleProps &particleProps);

	void OnUpdate(Rocket::Timestep ts);
	void OnRender();

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float RotationStart = 0.0f;
		float RotationEnd = 0.0f;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
};