#pragma once

#include "Core.h"
#include "GEEvent.h"
#include "GEWindow.h"
#include "GELayer.h"
namespace Rocket {

    class Application {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Close();

        void Run();

        static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}