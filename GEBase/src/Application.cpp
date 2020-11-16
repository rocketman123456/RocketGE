#include "GEBase/Log.h"
#include "GEBase/Application.h"
#include "GEEvent/ApplicationEvent.h"
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

        while(true) {

        }

        WindowCloseEvent close;
        RK_TRACE(close);
    }
}