#include "GEApplication/Application.h"

namespace Rocket
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        RK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create(WindowProps("Rocket Engine", 1280, 720)));
        m_Window->SetEventCallback(RK_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_GuiLayer = new ImGuiLayer();
        PushOverlay(m_GuiLayer);

        m_CurrentTime = m_Clock.now();
        m_LastTime = m_CurrentTime;
    }

    Application::~Application()
    {
        RK_CORE_INFO("Exit Application");
    }

    void Application::OnEvent(Event &e)
    {
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
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        RK_INFO("Start Application Run Loop");
        while (m_Running)
        {
            // Calculate Delta Time
            m_LastTime = m_CurrentTime;
            m_CurrentTime = m_Clock.now();
            m_Duration = m_CurrentTime - m_LastTime;
            // Common Update
            for (Layer *layer : m_LayerStack)
                layer->OnUpdate(Timestep(m_Duration.count()));
            // GUI Update
            m_GuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
                layer->OnGuiRender();
            m_GuiLayer->End();
            // Window Update
            m_Window->OnUpdate();
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
