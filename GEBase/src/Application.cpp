#include "GEBase/Log.h"
#include "GEBase/Application.h"
#include "GEEvent/ApplicationEvent.h"
#include "GEWindow/Window.h"

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

        auto window = Window::Create();

        while(true) {
            window->OnUpdate();
        }

        WindowCloseEvent close;
        RK_TRACE(close);
    }
}