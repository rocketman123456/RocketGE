#include "EditorLayer.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Rocket;

class CameraControllerScript : implements ScriptableEntity
{
public:
    virtual void OnCreate() override
    {
        auto& translation = GetComponent<TransformComponent>().Translation;
        translation.x = rand() % 10 - 5.0f;
    }

    virtual void OnDestroy() override
    {
    }

    virtual void OnUpdate(Timestep ts) override
    {
        auto& translation = GetComponent<TransformComponent>().Translation;
        auto& camera = GetComponent<CameraComponent>().Primary;

        float speed = 5.0f;

        if(!camera)
            return;

        if (Input::IsKeyPressed(Key::Left))
            translation.x -= speed * ts;
        if (Input::IsKeyPressed(Key::Right))
            translation.x += speed * ts;
        if (Input::IsKeyPressed(Key::Up))
            translation.y += speed * ts;
        if (Input::IsKeyPressed(Key::Down))
            translation.y -= speed * ts;
    }
};

class MovementScript : implements ScriptableEntity
{
    glm::vec3 m_Translation;
    float m_Time;
public:
    virtual void OnCreate() override
    {
        m_Translation = GetComponent<TransformComponent>().Translation;
    }

    virtual void OnDestroy() override
    {
    }

    virtual void OnUpdate(Timestep ts) override
    {
        auto& translation = GetComponent<TransformComponent>().Translation;

        translation.x = m_Translation.x + sinf(glm::radians(m_Time * 100.0f));
        translation.y = m_Translation.y + cosf(glm::radians(m_Time * 100.0f));
        m_Time = m_Time + ts;
    }
};

void EditorLayer::OnAttach()
{
    RK_PROFILE_FUNCTION();

    std::string checkboard_path = ProjectSourceDir + "/Assets/textures/Checkerboard.png";
    m_CheckerboardTexture = Texture2D::Create(checkboard_path);

    FramebufferSpecification fbSpec;
    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    m_Framebuffer = Framebuffer::Create(fbSpec);

    //m_Controller = new OrthographicCameraController(1280.0f / 720.0f);

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

    m_ActiveScene = CreateRef<Scene>();

#if 1
    // Entity
    auto square = m_ActiveScene->CreateEntity("Green Square");
    square.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

    auto redSquare = m_ActiveScene->CreateEntity("Red Square");
    redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    m_SquareEntity = square;

    m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
    m_CameraEntity.AddComponent<CameraComponent>();

    m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
    auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
    cc.Primary = false;

    m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraControllerScript>();
    m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraControllerScript>();

    redSquare.AddComponent<NativeScriptComponent>().Bind<MovementScript>();
#endif

    m_SceneHierarchyPanel.SetContext(m_ActiveScene);
}

void EditorLayer::OnDetach()
{
    RK_PROFILE_FUNCTION();

    //delete m_Controller;
    m_Texture.clear();
    m_ActiveScene.reset();
}

void EditorLayer::OnUpdate(Rocket::Timestep ts)
{
    // Resize
    if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
        (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
    {
        m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        //m_Controller->OnResize(m_ViewportSize.x, m_ViewportSize.y);
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }

    // Update
    //if (m_ViewportFocused && m_ViewportHovered)
    //    m_Controller->OnUpdate(ts);

    Renderer2D::ResetStats();

    m_Framebuffer->Bind();
    RenderCommand::SetClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderCommand::Clear();

    // Update scene
    m_ActiveScene->OnUpdate(ts);

    m_Framebuffer->Unbind();

    RenderCommand::SetClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderCommand::Clear();
}

void EditorLayer::OnEvent(Rocket::Event &event)
{
    //m_Controller->OnEvent(event);
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyPressedEvent>(RK_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
}

void EditorLayer::OnGuiRender()
{
    RK_PROFILE_FUNCTION();

    DockSpace();

    m_SceneHierarchyPanel.OnGuiRender();

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
    ImGui::End();

    ImGui::Begin("Scene");
    m_ViewportFocused = ImGui::IsWindowFocused();
    m_ViewportHovered = ImGui::IsWindowHovered();
    Application::Get().GetGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
    uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    m_ViewportSize = {viewportPanelSize.x, viewportPanelSize.y};
    ImGui::Image(reinterpret_cast<void *>(textureID), ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});
    ImGui::End();
}

void EditorLayer::DockSpace()
{
    // Note: Switch this to true to enable dockspace
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    style.WindowMinSize.x = minWinSizeX;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows, 
            // which we can't undo at the moment without finer window depth/z control.
            //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
            if (ImGui::MenuItem("New", "Ctrl+N"))
                NewScene();

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
                OpenScene();

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                SaveSceneAs();

            if (ImGui::MenuItem("Exit")) Application::Get().Close();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void EditorLayer::NewScene()
{
    m_ActiveScene = CreateRef<Scene>();
    m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);
}

void EditorLayer::OpenScene()
{
    std::string file_path = ProjectSourceDir + "/Assets/scenes/scene01.yaml";
    std::optional<std::string> filepath = FileDialogs::OpenFile(file_path.c_str());
    if (filepath)
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
        SceneSerializer serializer(m_ActiveScene);
        serializer.Deserialize(*filepath);
    }
}

void EditorLayer::SaveSceneAs()
{
    std::string file_path = ProjectSourceDir + "/Assets/scenes/scene01.yaml";
    std::optional<std::string> filepath = FileDialogs::SaveFile(file_path.c_str());
    if (filepath)
    {
        SceneSerializer serializer(m_ActiveScene);
        serializer.Serialize(*filepath);
    }
}

bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
{
    // Shortcuts
    if (e.GetRepeatCount() > 0)
        return false;

    bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
    bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
    switch (e.GetKeyCode())
    {
        case Key::N:
        {
            if (control)
                NewScene();

            break;
        }
        case Key::O:
        {
            if (control)
                OpenScene();

            break;
        }
        case Key::S:
        {
            if (control && shift)
                SaveSceneAs();

            break;
        }
    }

    return true;
}