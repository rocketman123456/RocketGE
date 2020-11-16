#include "GEBase/Log.h"
#include "GEBase/Application.h"

namespace Rocket {

    Application::Application() 
    {

    }

    Application::~Application() 
    {

    }

    void Application::Run() 
    {
        WindowResizeEvent resize(1280, 720);
        RK_TRACE(resize);

        m_Window = std::unique_ptr<Window>(Window::Create());

        while(true) {
            m_Window->OnUpdate();
        }

        WindowCloseEvent close;
        RK_TRACE(close);
    }
}