#include "Sandbox2D.h"
#include "Random.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>

extern float square_vertices_s[12];
extern uint32_t square_indices[6];

namespace Rocket {

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult_ profileResult)\
                            { m_ProfileResults.push_back(profileResult); })
    
    Application* CreateApplication()
    {
        return static_cast<Application*>(new Sandbox2D);
    }

    void Sandbox2DLayer::OnAttach()
    {
        RK_PROFILE_FUNCTION();

        std::string img_path_1 = ProjectSourceDir + "/Assets/textures/wall.jpg";
        std::string img_path_2 = ProjectSourceDir + "/Assets/textures/container.jpg";
        std::string img_path_3 = ProjectSourceDir + "/Assets/textures/texture.jpg";
        std::string img_path_4 = ProjectSourceDir + "/Assets/textures/Checkerboard.png";
        m_Texture.push_back(Texture2D::Create(img_path_1));
        m_Texture.push_back(Texture2D::Create(img_path_2));
        m_Texture.push_back(Texture2D::Create(img_path_3));
        m_Texture.push_back(Texture2D::Create(img_path_4));

        // Smoke
        m_SmokeParticle.Position = { 0.0f, 0.0f };
        m_SmokeParticle.Velocity = { 0.0f, 0.0f }, m_SmokeParticle.VelocityVariation = { 4.0f, 2.0f };
        m_SmokeParticle.SizeBegin = 0.35f, m_SmokeParticle.SizeEnd = 0.0f, m_SmokeParticle.SizeVariation = 0.15f;
        m_SmokeParticle.ColorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
        m_SmokeParticle.ColorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
        m_SmokeParticle.LifeTime = 4.0f;

        // Flames
        m_EngineParticle.Position = { 0.0f, 0.0f };
        m_EngineParticle.Velocity = { 0.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 0.1f, 0.1f };
        m_EngineParticle.SizeBegin = 0.5f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
        m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
        m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
        m_EngineParticle.LifeTime = 10.0f;

        m_Controller = new OrthographicCameraController(16.0f / 9.0f, false);

        Random::Init();
    }

	void Sandbox2DLayer::OnDetach()
    {
        RK_PROFILE_FUNCTION();
        
        delete m_Controller;
        m_Texture.clear();
    }

    void Sandbox2DLayer::OnUpdate(Timestep ts)
    {
        RK_PROFILE_FUNCTION();
        PROFILE_SCOPE("Sandbox2D::OnUpdate");

        Renderer2D::ResetStats();

        {
            PROFILE_SCOPE("CameraController::OnUpdate");
            m_Controller->OnUpdate(ts);

            if(Input::IsMouseButtonPressed(Mouse::ButtonLeft))
            {
                // Flames
                float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                
                glm::vec2 emissionPoint = { (r1 - 0.5f) / 2.0f, (r2 - 0.5f) / 2.0f };
                float rotation = r3 * 180.0f;
                m_EngineParticle.RotationStart = rotation;
                m_EngineParticle.RotationEnd = rotation;
                glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
                
                float x = Input::GetMouseX();
                float y = Input::GetMouseY();
                auto width = Rocket::Application::Get().GetWindow().GetWidth();
		        auto height = Rocket::Application::Get().GetWindow().GetHeight();
                auto bounds = m_Controller->GetBounds();
		        auto pos = m_Controller->GetCamera().GetPosition();
                x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		        y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
                m_Position = {x + pos.x, y + pos.y};

                float r4 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r5 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r6 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r7 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r8 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r9 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                m_EngineParticle.ColorBegin = { r4 * 255.0f / 255.0f, r5 * 255.0f / 255.0f, r6 * 255.0f / 255.0f, 0.8f };
                m_EngineParticle.ColorEnd = { r7 * 255.0f / 255.0f, r8 * 255.0f / 255.0f, r9 * 255.0f / 255.0f, 0.8f };

                float r10 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r11 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                
                m_EngineParticle.Position = m_Position + glm::vec2{ rotated.x, rotated.y };
                m_EngineParticle.Velocity = {(r10 - 0.5f) / 10.0f, (r11 - 0.5f) / 10.0f};
                //m_EngineParticle.Velocity = {0.0f, 0.0f};
                m_ParticleSystem.Emit(m_EngineParticle);
            }

            m_ParticleSystem.OnUpdate(ts);
        }
        {
            PROFILE_SCOPE("Renderer Prepare");
            RK_PROFILE_SCOPE("Renderer Prepare");
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();
        }
        {
            PROFILE_SCOPE("Renderer Draw");
            RK_PROFILE_SCOPE("Renderer Draw");
            Renderer2D::BeginScene(m_Controller->GetCamera());
            Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, {m_SquareColor, 1.0f});
            Renderer2D::DrawQuad({0.0f, 1.0f, -0.1f}, {0.9f, 0.9f}, glm::vec4(1.0f) - glm::vec4({m_SquareColor, 0.0f}));
            Renderer2D::DrawQuad({1.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[0]);
            Renderer2D::DrawQuad({1.0f, 1.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[1]);
            Renderer2D::DrawQuad({2.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[2]);
            Renderer2D::DrawQuad({0.0f, 0.0f, -0.2f}, {10.0f, 10.0f}, m_Texture[3], 10.0f);
            // For Benchmark
            for(float y = -5.0f; y < 4.5f; y += 0.5f)
            {
                for(float x = -5.0f; x < 4.5f; x += 0.5f)
                {
                    glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
                    Renderer2D::DrawQuad({0.5f + x, 0.5f + y, -0.15f}, {0.45f, 0.45f}, color);
                }
            }

            m_ParticleSystem.OnRender();

            //Renderer2D::DrawRotatedQuad({2.0f, 1.0f}, {0.9f, 0.9f}, (45.0f), m_Texture[3]);
            Renderer2D::EndScene();
        }
    }

    void Sandbox2DLayer::OnGuiRender()
    {
        RK_PROFILE_FUNCTION();

        ImGui::Begin("Setting");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::Separator();
        auto stats = Rocket::Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        ImGui::Separator();
        for (auto& result : m_ProfileResults)
        {
            char label[100];
            strcpy(label, "%.3fms ");
            strcat(label, result.Name);
            ImGui::Text(label, result.Time);
        }
        m_ProfileResults.clear();
        ImGui::End();
    }

    void Sandbox2DLayer::OnEvent(Event &event)
    {
        RK_PROFILE_FUNCTION();
        m_Controller->OnEvent(event);
        EventDispatcher dispatcher(event);
    }
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    void Sandbox2D::PreInitialize()
    {
        PushLayer(new Sandbox2DLayer());
    }

    void Sandbox2D::PreInitializeModule()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);

        PushModule(Rocket::g_ProcessManager);
        PushModule(Rocket::g_WindowManager);
        PushModule(Rocket::g_AudioManager);
    }
}
