#pragma once

#include "Core.h"
#include "GEEvent.h"
#include "GEWindow.h"

namespace Rocket {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}