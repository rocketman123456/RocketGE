#pragma once
#include "RKEngine.h"
#include "Panel/SceneHierarchyPanel.h"

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
    void DockSpace();

    void NewScene();
    void OpenScene();
    void SaveSceneAs();

    bool OnKeyPressed(Rocket::KeyPressedEvent& e);

private:
    //Rocket::OrthographicCameraController *m_Controller;

    Rocket::Ref<Rocket::Framebuffer> m_Framebuffer;
    Rocket::Ref<Rocket::VertexArray> m_SquareVA;
    Rocket::Ref<Rocket::Shader> m_FlatColorShader;
    Rocket::Ref<Rocket::Texture2D> m_CheckerboardTexture;
    std::vector<Rocket::Ref<Rocket::Texture2D>> m_Texture;
    std::unordered_map<char, Rocket::Ref<Rocket::SubTexture2D>> m_TextureMap;

    Rocket::Ref<Rocket::Scene> m_ActiveScene;
    Rocket::Entity m_SquareEntity;
    Rocket::Entity m_CameraEntity;
    Rocket::Entity m_SecondCamera;

    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_ViewportSize = {0.0f, 0.0f};
    glm::vec4 m_SquareColor = {1.0f, 0.5f, 0.2f, 1.0f};

    // Panels
    Rocket::SceneHierarchyPanel m_SceneHierarchyPanel;
};
