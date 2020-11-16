#include "GEBase/Log.h"
#include "GEBase/Application.h"

namespace Rocket {

    Application::Application() 
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() 
    {

    }

    void Application::Run() 
    {
        while(m_Running) 
        {
            m_Window->OnUpdate();
        }
    }
}