#pragma once

#include "Core.h"
#include "GEEvent/Event.h"

namespace Rocket {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}