#include "Sandbox2D.h"

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

        m_Controller.reset(new OrthographicCameraController(16.0f / 9.0f, false));
    }

	void Sandbox2DLayer::OnDetach()
    {
        RK_PROFILE_FUNCTION();
        
        m_Controller.reset();
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
            Renderer2D::DrawQuad({0.0f, 0.0f}, {0.9f, 0.9f}, {m_SquareColor, 1.0f});
            Renderer2D::DrawQuad({0.0f, 1.0f}, {0.9f, 0.9f}, glm::vec4(1.0f) - glm::vec4({m_SquareColor, 0.0f}));
            Renderer2D::DrawQuad({1.0f, 0.0f}, {0.9f, 0.9f}, m_Texture[0]);
            Renderer2D::DrawQuad({1.0f, 1.0f}, {0.9f, 0.9f}, m_Texture[1]);
            Renderer2D::DrawQuad({2.0f, 0.0f}, {0.9f, 0.9f}, m_Texture[2]);
            Renderer2D::DrawQuad({2.0f, 1.0f}, {0.9f, 0.9f}, m_Texture[3]);
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
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);
        PushLayer(new Sandbox2DLayer());
    }
}
