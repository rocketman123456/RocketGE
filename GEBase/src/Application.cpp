#include "GEBase/Log.h"
#include "GEBase/Application.h"

namespace Rocket {

    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        RK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(RK_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() 
    {

    }

    void Application::OnEvent(Event& e)
    {
        RK_CORE_TRACE(e);
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

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::Run() 
    {
        RK_INFO("Start Application Run Loop");
        while(m_Running) 
        {
            m_Window->OnUpdate();
        }
        RK_INFO("End Application Run Loop");
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return false;
	}
}
