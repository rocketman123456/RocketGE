#pragma once

#include "GECore/Core.h"
#include "GEEvent/Event.h"
#include "GEEvent/ApplicationEvent.h"
#include "GEWindow/Window.h"
#include "GELayer/Layer.h"
#include "GELayer/LayerStack.h"
#include "GEModule/AudioManager.h"
#include "GEInterface/IApplication.h"

namespace Rocket {
    Interface Application : implements IApplication
    {
    public:
        Application(const std::string& name = "Application") : IApplication(name) {}
        virtual ~Application() = default;

        virtual void PreInitialize() override {}
        virtual int Initialize() override;
        virtual void PostInitialize() override {}
        virtual void Finalize() override;

        virtual void PreInitializeModule() override {}
        virtual int InitializeModule() override;
        virtual void PostInitializeModule() override {}
        virtual void FinalizeModule() override;

        virtual void OnEvent(Event& e) override;
        void Close();

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        void PushModule(IRuntimeModule* module);

        virtual void TickModule() override;
        virtual void Tick() override;
        virtual void Tick(Timestep ts) override {}

        inline Window& GetWindow() { return *m_Window; }
        inline bool GetIsRunning() override { return m_Running; }
        static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
    private:
        Ref<Window> m_Window;
        Layer* m_GuiLayer;
        LayerStack m_LayerStack;

        std::vector<IRuntimeModule*> m_Modules;
        std::unordered_map<std::string, IRuntimeModule*> m_ModulesMap;

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