#pragma once

#include "Components/Position.h"
#include "Components/Tile.h"
#include "ViewPort.h"

#include "RKEngine.h"

#include <glm/glm.hpp>

class HazelDashLayer : public Rocket::Layer
{
public:
	HazelDashLayer();
	virtual ~HazelDashLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Rocket::Timestep ts) override;

#ifdef RK_DEBUG
	virtual void OnGuiRender() override;
#endif

	void OnEvent(Rocket::Event &e) override;

private:
	bool OnKeyPressed(Rocket::KeyPressedEvent &e);

	void LoadScene(int level);

	// game "systems" and "events" (TODO: rework into proper systems and events, later...)
	void PhysicsFixedUpdate();
	void PlayerControllerFixedUpdate();
	void EnemiesFixedUpdate();
	void OnExplode(const Position &pos);
	void AmoebaFixedUpdate();
	void OnSolidify(const Tile solidfyTo);
	void PlayerControllerUpdate(Rocket::Timestep ts);
	bool TryMovePlayer(Position &pos, Position direction, const bool ctrlPressed);
	void OnPlayerMoved(const Position &pos);
	void OnPlayerDied();
	void OnLevelCompleted();
	void OnIncreaseScore();
	void ExploderUpdate(Rocket::Timestep ts);
	void AnimatorUpdate(Rocket::Timestep ts);
	void CameraControllerUpdate(Rocket::Timestep ts);
	void RendererUpdate(Rocket::Timestep ts);

	Rocket::Entity GetEntity(const Position pos);
	void SetEntity(Position pos, Rocket::Entity entity);
	void ClearEntity(const Position pos);
	void SwapEntities(const Position posA, const Position posB);

private:
	std::array<Rocket::Ref<Rocket::Texture2D>, (size_t)Tile::NumTiles> m_Tiles;

	Rocket::Scene m_Scene;
	// TODO: Maybe viewport (and associated camera) should be components of a "camera entity" that belongs to the scene...?
	ViewPort m_ViewPort;
	std::vector<Rocket::Entity> m_Entities;
	Rocket::Entity m_EmptyEntity;
	Rocket::Entity m_ExitEntity;

	Rocket::Timestep m_FixedTimestep;
	Rocket::Timestep m_AnimationTimestep;
	float m_FixedUpdateAccumulatedTs; // Might be be better as a Hazel::Timestep, but that class doesnt support operator +=
	float m_AnimatorAccumulatedTs;	  // Might be be better as a Hazel::Timestep, but that class doesnt support operator +=

	float m_PushProbability;

	int m_CurrentLevel;
	int m_Width;
	int m_Height;
	int m_Score;
	int m_ScoreRequired;
	int m_AmoebaSize;
	int m_AmoebaPotential;

	bool m_GamePaused;
	bool m_PlayerIsAlive; // if false, then pressing spacebar restarts.  Otherwise, pressing spacebar pauses
	bool m_WonLevel;
};
