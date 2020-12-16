#include "Sandbox2D.h"
#include "Random.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>

extern float square_vertices_s[12];
extern uint32_t square_indices[6];

static uint32_t s_MapWidth = 24;
static uint32_t s_MapHeight = 12;
static const char* s_MapTiles = 
    "WWWWWWWWWWWWWWWWWWWWWWWW"
    "WWWDDDDDDDDDDDDDDDWWWWWW"
    "WWWDDDDDDDDDDDDDDDDWWWWW"
    "WWWWWDDDDDDDDDDDDDDDDWWW"
    "WWWDDDDDDDDWWWWWDDDWWWWW"
    "WWWWDDDDWWWWWWWWWWWWWWWW"
    "WWWWDDDDDDDDDDDDDDDDWWWW"
    "WWWDDDDDDDDWWWWWWWWWWWWW"
    "WWWDDDDDWWWWWWWWDDDWWWWW"
    "WWWWDDDDDDDDWWWWWWWWWWWW"
    "WWWWWWWDDDDDDDDDDDDDWWWW"
    "WWWWWWWWWWWWWWWWWWWWWWWW"
;

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
        std::string img_path_5 = ProjectSourceDir + "/Assets/textures/RPGpack_sheet_2X.png";
        m_Texture.push_back(Texture2D::Create(img_path_1));
        m_Texture.push_back(Texture2D::Create(img_path_2));
        m_Texture.push_back(Texture2D::Create(img_path_3));
        m_Texture.push_back(Texture2D::Create(img_path_4));
        m_Texture.push_back(Texture2D::Create(img_path_5));

        // Flames
        m_EngineParticle.Position = { 0.0f, 0.0f };
        m_EngineParticle.Velocity = { 0.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 0.1f, 0.1f };
        m_EngineParticle.SizeBegin = 0.5f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
        m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
        m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
        m_EngineParticle.LifeTime = 10.0f;

        m_Controller = new OrthographicCameraController(16.0f / 9.0f, false);

        m_TextureMap['D'] = SubTexture2D::Create(m_Texture[4], { 6, 11}, {128.0f, 128.0f});
        m_TextureMap['W'] = SubTexture2D::Create(m_Texture[4], {11, 11}, {128.0f, 128.0f});

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

        Renderer2D::ResetStats();

        {
            m_Controller->OnUpdate(ts);
        }
        {
            RK_PROFILE_SCOPE("Renderer Prepare");

            if(Input::IsMouseButtonPressed(Mouse::ButtonLeft))
            {
                // Flames
                float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r3_1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float r3_2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                
                glm::vec2 emissionPoint = { (r1 - 0.5f) / 2.0f, (r2 - 0.5f) / 2.0f };
                float rotation_1 = r3_1 * 180.0f;
                float rotation_2 = r3_2 * 180.0f;
                m_EngineParticle.RotationStart = rotation_1;
                m_EngineParticle.RotationEnd = rotation_2;
                
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
                
                m_EngineParticle.Position = m_Position;
                m_EngineParticle.Velocity = {(r10 - 0.5f) / 10.0f, (r11 - 0.5f) / 10.0f};
                //m_EngineParticle.Velocity = {0.0f, 0.0f};
                m_ParticleSystem.Emit(m_EngineParticle);
            }
            m_ParticleSystem.OnUpdate(ts);

            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();
        }
        {
            RK_PROFILE_SCOPE("Renderer Draw");
            Renderer2D::BeginScene(m_Controller->GetCamera());
            
            //DrawQuads();
            DrawMap();

            m_ParticleSystem.OnRender();

            Renderer2D::EndScene();
        }
    }

    void Sandbox2DLayer::DrawMap()
    {
        for(int y = 0; y < s_MapHeight; ++y)
        {
            for(int x = 0; x < s_MapWidth; ++x)
            {
                char key = s_MapTiles[x + y*s_MapWidth];
                if(m_TextureMap.find(key) != m_TextureMap.end())
                    Renderer2D::DrawQuad({x - s_MapWidth / 2.0f, y - s_MapHeight / 2.0f, -0.1f}, {1.0f, 1.0f}, m_TextureMap[key]);
                else
                    Renderer2D::DrawQuad({x - s_MapWidth / 2.0f, y - s_MapHeight / 2.0f, -0.01}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
            }
        }
    }

    void Sandbox2DLayer::DrawQuads()
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

    void Sandbox2DLayer::OnGuiRender()
    {
        RK_PROFILE_FUNCTION();

        DockSpace();

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
        auto textureid = m_Texture[3]->GetRendererID();
        ImGui::Image((void*)textureid, ImVec2({100, 100}));
        ImGui::End();
    }

    void Sandbox2DLayer::DockSpace()
    {
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        bool show_app_dockspace = true;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &show_app_dockspace, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Docking"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
                if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
                if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
                if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
                ImGui::Separator();
                if (ImGui::MenuItem("Close DockSpace"))
                    show_app_dockspace = false;
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                    Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

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
