#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rocket;

void EditorLayer::OnAttach()
{
    std::string checkboard_path = ProjectSourceDir + "/Assets/textures/Checkerboard.png";
    m_CheckerboardTexture = Texture2D::Create(checkboard_path);

    FramebufferSpecification fbSpec;
    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    m_Framebuffer = Framebuffer::Create(fbSpec);

    m_Controller = new OrthographicCameraController(1280.0f / 720.0f);

    std::string img_path_1 = ProjectSourceDir + "/Assets/textures/wall.jpg";
    std::string img_path_2 = ProjectSourceDir + "/Assets/textures/container.jpg";
    std::string img_path_3 = ProjectSourceDir + "/Assets/textures/texture.jpg";
    std::string img_path_4 = ProjectSourceDir + "/Assets/textures/Checkerboard.png";
    std::string img_path_5 = ProjectSourceDir + "/Assets/textures/RPGpack_sheet_2X.png";
    m_Texture.push_back(Texture2D::Create(img_path_1));
    m_Texture.push_back(Texture2D::Create(img_path_2));
    m_Texture.push_back(Texture2D::Create(img_path_3));
    m_Texture.push_back(Texture2D::Create(img_path_4));
    m_Texture.push_back(Texture2D::Create(img_path_5));
}

void EditorLayer::OnDetach()
{
    delete m_Controller;
    m_Texture.clear();
}

void EditorLayer::OnUpdate(Rocket::Timestep ts)
{
    // Resize
    if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
        (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
    {
        m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_Controller->OnResize(m_ViewportSize.x, m_ViewportSize.y);
    }

    Renderer2D::ResetStats();

    m_Framebuffer->Bind();
    RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
    RenderCommand::Clear();
    Renderer2D::BeginScene(m_Controller->GetCamera());
    DrawQuads();
    Renderer2D::EndScene();
    m_Framebuffer->Unbind();

    RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
    RenderCommand::Clear();
}

void EditorLayer::DrawQuads()
{
    Renderer2D::DrawQuad({0.0f, 0.0f, -0.2f}, {10.0f, 10.0f}, m_Texture[3], 10.0f);
    Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, {m_SquareColor, 1.0f});
    Renderer2D::DrawQuad({0.0f, 1.0f, -0.1f}, {0.9f, 0.9f}, glm::vec4(1.0f) - glm::vec4({m_SquareColor, 0.0f}));
    Renderer2D::DrawQuad({1.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[0]);
    Renderer2D::DrawQuad({1.0f, 1.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[1]);
    Renderer2D::DrawQuad({2.0f, 0.0f, -0.1f}, {0.9f, 0.9f}, m_Texture[2]);
    
    for(float y = -5.0f; y < 4.5f; y += 0.5f)
    {
        for(float x = -5.0f; x < 4.5f; x += 0.5f)
        {
            glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
            Renderer2D::DrawQuad({0.5f + x, 0.5f + y, -0.15f}, {0.45f, 0.45f}, color);
        }
    }

    auto sub_texture = SubTexture2D::Create(m_Texture[4], {7, 6}, {128.0f, 128.0f});
    Renderer2D::DrawQuad({2.0f, 1.0f, -0.1f}, {0.9f, 0.9f}, sub_texture);
}

void EditorLayer::OnEvent(Rocket::Event& event)
{

}

void EditorLayer::OnGuiRender()
{
    ImGui::Begin("Setting");

    m_ViewportFocused = ImGui::IsWindowFocused();
    m_ViewportHovered = ImGui::IsWindowHovered();
    uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
    
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::Separator();
    auto stats = Rocket::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::Separator();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y });
    ImGui::End();
}