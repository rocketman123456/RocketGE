#pragma once

#include "RKEngine.h"

#include "Level.h"
#include <imgui.h>

class GameLayer : public Rocket::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rocket::Timestep ts) override;
	virtual void OnGuiRender() override;
	void OnEvent(Rocket::Event& e) override;
	bool OnMouseButtonPressed(Rocket::MouseButtonPressedEvent& e);
	bool OnWindowResize(Rocket::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Rocket::Scope<Rocket::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};