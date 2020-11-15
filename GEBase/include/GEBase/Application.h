#pragma once

namespace Rocket {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}