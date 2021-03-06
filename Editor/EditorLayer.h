#pragma once
#include "RKEngine.h"

class EditorLayer : implements Rocket::Layer
{
public:
    EditorLayer() : Rocket::Layer("EditorLayer") {}

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Rocket::Timestep ts) override;
    virtual void OnEvent(Rocket::Event &event) override;
    // GUI Related Function
    virtual void OnGuiRender() override;

private:
    void DrawQuads();
    void DockSpace();

private:
    Rocket::OrthographicCameraController *m_Controller;

    Rocket::Ref<Rocket::Framebuffer> m_Framebuffer;
    Rocket::Ref<Rocket::Texture2D> m_CheckerboardTexture;
    std::vector<Rocket::Ref<Rocket::Texture2D>> m_Texture;
    std::unordered_map<char, Rocket::Ref<Rocket::SubTexture2D>> m_TextureMap;

    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    glm::vec3 m_SquareColor = {1.0f, 0.5f, 0.2f};
};
