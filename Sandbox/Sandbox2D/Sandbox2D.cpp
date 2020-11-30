#include "Sandbox2D.h"
#include "GERender/Renderer.h"
#include "GERender2D/Renderer2D.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float square_vertices_s[12];
extern uint32_t square_indices[6];

namespace Rocket {
    Application* CreateApplication()
    {
        return static_cast<Application*>(new Sandbox2D);
    }

    Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer")
    {
    }

    void Sandbox2DLayer::OnAttach()
    {
        m_Controller.reset(new OrthographicCameraController(16.0f / 9.0f, false));
    }

	void Sandbox2DLayer::OnDetach()
    {
        m_Controller.reset();
    }

    void Sandbox2DLayer::OnUpdate(Timestep ts)
    {
        m_Controller->OnUpdate(ts);

        RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        RenderCommand::Clear();

        Renderer2D::BeginScene(m_Controller->GetCamera());
        Renderer2D::DrawQuad({0.0f, 0.0f}, {0.9f, 0.9f}, {m_SquareColor, 1.0f});
        Renderer2D::DrawQuad({1.0f, 0.0f}, {0.9f, 0.9f}, {m_SquareColor, 1.0f});
        Renderer2D::EndScene();
    }

    void Sandbox2DLayer::OnGuiRender()
    {
        ImGui::Begin("Example");
        ImGui::Text("Hello Example!");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void Sandbox2DLayer::OnEvent(Event &event)
    {
        m_Controller->OnEvent(event);

        EventDispatcher dispatcher(event);
    }
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    Sandbox2D::Sandbox2D()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);
        PushLayer(new Sandbox2DLayer());
    }

    Sandbox2D::~Sandbox2D()
    {

    }
}
