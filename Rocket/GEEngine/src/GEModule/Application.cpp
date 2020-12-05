#include "GEModule/Application.h"
#include "GELayer/ImGuiLayer.h"
#include "GERender/Renderer.h"
#include "GERender2D/Renderer2D.h"
#include "GEUtils/Profile.h"
#include "GEUtils/Instrumentor.h"

namespace Rocket
{
    Application *Application::s_Instance = nullptr;

    int Application::Initialize()
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
        ProfilerInit();

        return 0;
    }

    void Application::Finalize()
    {
        RK_PROFILE_FUNCTION();

        Renderer::Shutdown();
        RK_CORE_INFO("Exit Application");
    }

    int Application::InitializeModule()
    {
        int ret = 0;
        for (auto& module : m_Modules)
        {
            if ((ret = module->Initialize()) != 0) {
                RK_CORE_ERROR("Failed. err = {0}", ret);
                return ret;
            }
        }
        return ret;
    }

    void Application::FinalizeModule()
    {
        for (auto& module : m_Modules)
        {
            module->Finalize();
            delete module;
        }
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

    void Application::PushModule(IRuntimeModule* module)
    {
        m_Modules.push_back(module);
    }

    void Application::TickModule()
    {
        for (auto& module : m_Modules)
        {
            module->Tick(Timestep(m_Duration.count()));
        }
    }

    void Application::Tick()
    {
        RK_PROFILE_FUNCTION();

        // Calculate Delta Time
        m_LastTime = m_CurrentTime;
        m_CurrentTime = m_Clock.now();
        m_Duration = m_CurrentTime - m_LastTime;

        {
            RK_PROFILE_SCOPE("Profiler Start Loop");
            ProfilerBegin("Main Loop");
        }
        // Common Update
        ProfilerBegin("Layer Update");
        for (Layer *layer : m_LayerStack)
        {
            RK_PROFILE_SCOPE("Layer Update");
            ProfilerBegin(layer->GetName());
            layer->OnUpdate(Timestep(m_Duration.count()));
            ProfilerEnd(layer->GetName());
        }
        ProfilerEnd("Layer Update");
        // GUI Update
        {
            RK_PROFILE_SCOPE("GuiLayer Begin");
            ProfilerBegin("GuiLayer Begin");
            m_GuiLayer->Begin();
            ProfilerEnd("GuiLayer Begin");
        }
        ProfilerBegin("GuiLayer Update");
        for (Layer *layer : m_LayerStack)
        {
            RK_PROFILE_SCOPE("GuiLayer Update");
            ProfilerBegin(layer->GetName() + " GUI");
            layer->OnGuiRender();
            ProfilerEnd(layer->GetName() + " GUI");
        }
        ProfilerEnd("GuiLayer Update");
        {
            RK_PROFILE_SCOPE("GuiLayer End");
            ProfilerBegin("GuiLayer End");
            m_GuiLayer->End();
            ProfilerEnd("GuiLayer End");
        }
        // Window Update
        {
            RK_PROFILE_SCOPE("Window Update");
            ProfilerBegin("Window Update");
            m_Window->OnUpdate();
            ProfilerEnd("Window Update");
        }
        {
            RK_PROFILE_SCOPE("Profiler End Loop");
            ProfilerEnd("Main Loop");
        }
        {
            RK_PROFILE_SCOPE("Profiler Dump");
            ProfilerDump();
        }
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
