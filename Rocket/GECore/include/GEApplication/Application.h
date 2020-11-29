#pragma once

#include "GECore.h"
#include "GEEvent.h"
#include "GEWindow.h"
#include "GELayer.h"
#include "GERender.h"

namespace Rocket {
    Interface Application {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Close();

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        void Run();

        inline Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
    private:
        Scope<Window> m_Window;
        Layer* m_GuiLayer;
        LayerStack m_LayerStack;

        bool m_Running = true;
        bool m_Minimized = false;

        std::chrono::steady_clock m_Clock;
        std::chrono::duration<double> m_Duration;
        std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;
        std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}