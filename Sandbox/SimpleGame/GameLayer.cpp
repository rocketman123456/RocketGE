#include "GameLayer.h"
#include <imgui.h>
#include "GEModule/AudioManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rocket;

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto &window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

static std::vector<std::string> audio_names;

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	std::string path_front = ProjectSourceDir + "/Assets/fonts/opensans/OpenSans-Regular.ttf";
	m_Font = io.Fonts->AddFontFromFileTTF(path_front.c_str(), 120.0f);

	std::string A0_1 = "Piano.ff.C2";
	std::string A1_1 = "Piano.ff.D2";
	std::string A2_1 = "Piano.ff.E2";
	std::string A3_1 = "Piano.ff.F2";
	std::string A4_1 = "Piano.ff.G2";
	std::string A5_1 = "Piano.ff.A2";
	std::string A6_1 = "Piano.ff.B2";
	//std::string A7_1 = "Piano.ff.C3";

	std::string A0 = "Piano.ff.C3";
	std::string A1 = "Piano.ff.D3";
	std::string A2 = "Piano.ff.E3";
	std::string A3 = "Piano.ff.F3";
	std::string A4 = "Piano.ff.G3";
	std::string A5 = "Piano.ff.A3";
	std::string A6 = "Piano.ff.B3";
	std::string A7 = "Piano.ff.C4";

	//std::string A0_2 = "Piano.ff.C4";
	std::string A1_2 = "Piano.ff.D4";
	std::string A2_2 = "Piano.ff.E4";
	std::string A3_2 = "Piano.ff.F4";
	std::string A4_2 = "Piano.ff.G4";
	std::string A5_2 = "Piano.ff.A4";
	std::string A6_2 = "Piano.ff.B4";
	std::string A7_2 = "Piano.ff.C5";

	audio_names.clear();
	audio_names.push_back(A0_1);
	audio_names.push_back(A1_1);
	audio_names.push_back(A2_1);
	audio_names.push_back(A3_1);
	audio_names.push_back(A4_1);
	audio_names.push_back(A5_1);
	audio_names.push_back(A6_1);

	audio_names.push_back(A0);
	audio_names.push_back(A1);
	audio_names.push_back(A2);
	audio_names.push_back(A3);
	audio_names.push_back(A4);
	audio_names.push_back(A5);
	audio_names.push_back(A6);
	audio_names.push_back(A7);

	audio_names.push_back(A1_2);
	audio_names.push_back(A2_2);
	audio_names.push_back(A3_2);
	audio_names.push_back(A4_2);
	audio_names.push_back(A5_2);
	audio_names.push_back(A6_2);
	audio_names.push_back(A7_2);

	srand(rand());
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

	const auto &playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({playerPos.x, playerPos.y, 0.0f});

	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level.OnUpdate(ts);
		break;
	}
	default:
		break;
	}

	// Render
	Rocket::RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1});
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

void GameLayer::OnEvent(Rocket::Event &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(RK_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(RK_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<KeyPressedEvent>(RK_BIND_EVENT_FN(GameLayer::OnKeyEvent));
}

bool GameLayer::OnKeyEvent(Rocket::KeyPressedEvent &e)
{
	if (m_State == GameState::Play)
	{
		int i = rand() % audio_names.size();

		if (e.GetKeyCode() == Key::Space)
		{
			g_AudioManager->PlayAudio(audio_names[i]);
		}
	}
	return false;
}

bool GameLayer::OnMouseButtonPressed(Rocket::MouseButtonPressedEvent &e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Rocket::WindowResizeEvent &e)
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
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}
