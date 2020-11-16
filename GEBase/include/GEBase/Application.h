#pragma once

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