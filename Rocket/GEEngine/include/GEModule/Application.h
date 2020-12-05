#pragma once

#include "GECore/Core.h"
#include "GEEvent/Event.h"
#include "GEEvent/ApplicationEvent.h"
#include "GEWindow/Window.h"
#include "GELayer/Layer.h"
#include "GELayer/LayerStack.h"
#include "GEModule/AudioManager.h"

namespace Rocket {
    Interface Application {
    public:
        Application() {}
        virtual ~Application() = default;

        virtual void PreInitialize() {}
        virtual int Initialize();
        virtual void PostInitialize() {}
        virtual void Finalize();

        virtual void PreInitializeModule() {}
        virtual int InitializeModule();
        virtual void PostInitializeModule() {}
        virtual void FinalizeModule();

        void OnEvent(Event& e);
        void Close();

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        void PushModule(IRuntimeModule* module);

        void TickModule();
        void Tick();

        inline Window& GetWindow() { return *m_Window; }
        inline bool GetIsRunning() { return m_Running; }
        static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
    private:
        Scope<Window> m_Window;
        Layer* m_GuiLayer;
        LayerStack m_LayerStack;

        std::vector<IRuntimeModule*> m_Modules;

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