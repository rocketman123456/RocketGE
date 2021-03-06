#pragma once

#include "GECore/Core.h"
#include "GEInterface/IApplication.h"
#include "GEEvent/Event.h"
#include "GEEvent/ApplicationEvent.h"
#include "GEWindow/Window.h"
#include "GELayer/Layer.h"
#include "GELayer/ImGuiLayer.h"
#include "GELayer/LayerStack.h"
#include "GEUtils/ThreadPool.h"

namespace Rocket
{
    Interface Application : implements IApplication
    {
    public:
        Application(const std::string &name = "Application") : IApplication(name) {}
        virtual ~Application() = default;

        virtual void PreInitialize() override {}
        virtual int Initialize() override;
        virtual void PostInitialize() override {}
        virtual void Finalize() override;

        virtual void PreInitializeModule() override {}
        virtual int InitializeModule() override;
        virtual void PostInitializeModule() override {}
        virtual void FinalizeModule() override;

        virtual void OnEvent(Event & e) override;
        void Close();

        void PushLayer(Layer * layer);
        void PushOverlay(Layer * layer);
        void PopLayer(Layer * layer);
        void PopOverlay(Layer * layer);

        void PushModule(IRuntimeModule * module);

        virtual void TickModule() override;
        virtual void Tick() override;

        inline ImGuiLayer *GetGuiLayer() { return m_GuiLayer; }
        inline Window &GetWindow() { return *m_Window; }
        inline bool GetIsRunning() override { return m_Running; }
        static Application &Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent & e);
        bool OnWindowResize(WindowResizeEvent & e);

    private:
        Ref<Window> m_Window;
        ImGuiLayer *m_GuiLayer;
        LayerStack m_LayerStack;

        std::vector<IRuntimeModule *> m_Modules;

        thread_pool m_ThreadPool;

        bool m_Running = true;
        bool m_Minimized = false;
        bool m_Parallel = true;

        std::chrono::steady_clock m_Clock;
        std::chrono::duration<double> m_Duration;
        std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;
        std::chrono::time_point<std::chrono::steady_clock> m_LastTime;

    private:
        static Application *s_Instance;
    };

    Application *CreateApplication();
} // namespace Rocket