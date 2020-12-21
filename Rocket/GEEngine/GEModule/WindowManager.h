#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEWindow/Window.h"

namespace Rocket
{
    class WindowManager : implements IRuntimeModule
    {
    public:
        WindowManager() : IRuntimeModule("WindowManager") {}
        virtual ~WindowManager() = default;

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual int Tick(Timestep ts) override;
        virtual void OnEvent(Event &event) override;

        Ref<Window> GetWindow() { return m_Window; }

    private:
        Ref<Window> m_Window;
    };

    extern WindowManager *g_WindowManager;
} // namespace Rocket