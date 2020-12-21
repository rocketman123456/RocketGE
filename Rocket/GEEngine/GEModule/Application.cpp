#include "GEModule/Application.h"
#include "GELayer/ImGuiLayer.h"
#include "GERender/Renderer.h"
#include "GERender2D/Renderer2D.h"
#include "GEUtils/Profile.h"
#include "GEUtils/Instrumentor.h"
#include "GEModule/WindowManager.h"

namespace Rocket
{
    Application *Application::s_Instance = nullptr;

    int Application::Initialize()
    {
        RK_PROFILE_FUNCTION();

        m_Window->SetEventCallback(RK_BIND_EVENT_FN(Application::OnEvent));

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
        RK_CORE_INFO("Exit Application");
    }

    int Application::InitializeModule()
    {
        RK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        int ret = 0;
        for (auto& module : m_Modules)
        {
            if ((ret = module->Initialize()) != 0) {
                RK_CORE_ERROR("Failed. err = {0}", ret);
                return ret;
            }
        }

        m_Window = g_WindowManager->GetWindow();
        Renderer::Init();

        return ret;
    }

    void Application::FinalizeModule()
    {
        for (auto& module : m_Modules)
        {
            module->Finalize();
            delete module;
        }

        Renderer::Shutdown();
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
    }

    void Application::PushOverlay(Layer *layer)
    {
        RK_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
    }

    void Application::PopLayer(Layer* layer)
    {
        RK_PROFILE_FUNCTION();
        m_LayerStack.PopLayer(layer);
    }

    void Application::PopOverlay(Layer* layer)
    {
        RK_PROFILE_FUNCTION();
        m_LayerStack.PopOverlay(layer);
    }

    void Application::PushModule(IRuntimeModule* module)
    {
        m_Modules.push_back(module);
    }

    void Application::Tick()
    {
        RK_PROFILE_FUNCTION();

        // Calculate Delta Time
        m_LastTime = m_CurrentTime;
        m_CurrentTime = m_Clock.now();
        m_Duration = m_CurrentTime - m_LastTime;

        m_Window->PollEvent();

        {
            RK_PROFILE_SCOPE("Profiler Start Loop");
            ProfilerBegin("Layer Tick");
        }
        // Common Update
        {
            ProfilerBegin("Layer Update");
            for (Layer *layer : m_LayerStack)
            {
                RK_PROFILE_SCOPE("Layer Update");
                ProfilerBegin(layer->GetName());
                layer->OnUpdate(Timestep(m_Duration.count()));
                ProfilerEnd(layer->GetName());
            }
            ProfilerEnd("Layer Update");
        }
        // GUI Update
        {
            RK_PROFILE_SCOPE("GuiLayer Begin");
            ProfilerBegin("GuiLayer Begin");
            m_GuiLayer->Begin();
            ProfilerEnd("GuiLayer Begin");
        }
        {
            ProfilerBegin("GuiLayer Update");
            for (Layer *layer : m_LayerStack)
            {
                RK_PROFILE_SCOPE("GuiLayer Update");
                ProfilerBegin(layer->GetName() + " GUI");
                layer->OnGuiRender();
                ProfilerEnd(layer->GetName() + " GUI");
            }
            ProfilerEnd("GuiLayer Update");
        }
        {
            RK_PROFILE_SCOPE("GuiLayer End");
            ProfilerBegin("GuiLayer End");
            m_GuiLayer->End();
            ProfilerEnd("GuiLayer End");
        }
        {
            RK_PROFILE_SCOPE("Profiler End Loop");
            ProfilerEnd("Layer Tick");
        }
    }

    void Application::TickModule()
    {
        RK_PROFILE_FUNCTION();
        
        if(m_Parallel) {
            ProfilerBegin("Module Tick Parallel");

            std::vector< std::future<int> > futures;

            for (auto& module : m_Modules)
            {
                futures.push_back( 
                    m_ThreadPool.enqueue_task(&IRuntimeModule::Tick, module, Timestep(m_Duration.count())) 
                );
            }

            for(auto& f : futures)
                f.wait();

            for(auto& f : futures)
                f.get();
            
            ProfilerEnd("Module Tick Parallel");
        }
        else {
            ProfilerBegin("Module Tick");
            for (auto& module : m_Modules)
            {
                RK_PROFILE_SCOPE(module->GetName());
                ProfilerBegin(module->GetName());
                module->Tick(Timestep(m_Duration.count()));
                ProfilerEnd(module->GetName());
            }
            ProfilerEnd("Module Tick");
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
