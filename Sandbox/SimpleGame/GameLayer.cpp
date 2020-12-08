#include "GameLayer.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rocket;

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
    std::string path_front = ProjectSourceDir + "/Assets/fonts/opensans/OpenSans-Regular.ttf";
	m_Font = io.Fonts->AddFontFromFileTTF(path_front.c_str(), 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Rocket::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
		case GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
	}

	// Render
	Rocket::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Rocket::RenderCommand::Clear();

	Rocket::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Rocket::Renderer2D::EndScene();
}

void GameLayer::OnGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnGuiRender();
	//ImGui::End();

	switch (m_State)
	{
		case GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
			break;
		}
		case GameState::MainMenu:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
			break;
		}
		case GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = Application::Get().GetWindow().GetWidth();
			auto height = Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}

void GameLayer::OnEvent(Rocket::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(RK_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(RK_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Rocket::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Rocket::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top *aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
