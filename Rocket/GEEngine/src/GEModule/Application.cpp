#include "GEModule/Application.h"
#include "GELayer/ImGuiLayer.h"
#include "GERender/Renderer.h"
#include "GERender2D/Renderer2D.h"
#include "GEUtils/Profile.h"
#include "GEUtils/Instrumentor.h"

namespace Rocket
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        RK_PROFILE_FUNCTION();

        RK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create({"Rocket Engine", 1280, 720});
        m_Window->SetEventCallback(RK_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_GuiLayer = new ImGuiLayer();
        PushOverlay(m_GuiLayer);

        m_CurrentTime = m_Clock.now();
        m_LastTime = m_CurrentTime;

        // for realtime loop profile
        g_Profiler->ProfileInit();
    }

    Application::~Application()
    {
        RK_PROFILE_FUNCTION();

        Renderer::Shutdown();
        RK_CORE_INFO("Exit Application");
    }

    void Application::OnEvent(Event &e)
    {
        RK_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(RK_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(RK_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer *layer)
    {
        RK_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        RK_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        RK_INFO("Start Application Run Loop");
        while (m_Running)
        {
            RK_PROFILE_FUNCTION();

            // Calculate Delta Time
            m_LastTime = m_CurrentTime;
            m_CurrentTime = m_Clock.now();
            m_Duration = m_CurrentTime - m_LastTime;

            {
                RK_PROFILE_SCOPE("Profiler Start Loop");
                g_Profiler->ProfileBegin("Main Loop");
            }
            // Common Update
            for (Layer *layer : m_LayerStack)
            {
                RK_PROFILE_SCOPE("Layer Update");
                g_Profiler->ProfileBegin(layer->GetName());
                layer->OnUpdate(Timestep(m_Duration.count()));
                g_Profiler->ProfileEnd(layer->GetName());
            }
            // GUI Update
            {
                RK_PROFILE_SCOPE("Layer GUI Begin");
                g_Profiler->ProfileBegin("GuiLayer Begin");
                m_GuiLayer->Begin();
                g_Profiler->ProfileEnd("GuiLayer Begin");
            }
            for (Layer *layer : m_LayerStack)
            {
                RK_PROFILE_SCOPE("Layer GUI Update");
                g_Profiler->ProfileBegin(layer->GetName() + " GUI");
                layer->OnGuiRender();
                g_Profiler->ProfileEnd(layer->GetName() + " GUI");
            }
            {
                RK_PROFILE_SCOPE("Layer GUI End");
                g_Profiler->ProfileBegin("GuiLayer End");
                m_GuiLayer->End();
                g_Profiler->ProfileEnd("GuiLayer End");
            }
            // Window Update
            {
                RK_PROFILE_SCOPE("Window Update");
                m_Window->OnUpdate();
            }
            {
                RK_PROFILE_SCOPE("Profiler End Loop");
                g_Profiler->ProfileEnd("Main Loop");
            }
            {
                RK_PROFILE_SCOPE("Profiler Update");
                g_Profiler->ProfileDumpOutputToBuffer();
            }
        }
        RK_INFO("End Application Run Loop");
    }

    void Application::Close()
    {
        m_Running = false;
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        Close();
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        RK_PROFILE_FUNCTION();
        
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight(), e.GetXScale(), e.GetYScale());
        return false;
    }
}
