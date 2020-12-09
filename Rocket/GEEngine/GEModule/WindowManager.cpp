#include "GEModule/WindowManager.h"

namespace Rocket {
    WindowManager* g_WindowManager = new WindowManager();

    int WindowManager::Initialize()
    {
        m_Window = Window::Create({"Rocket Engine", 1280, 720});
        return 0;
    }

    void WindowManager::Finalize()
    {

    }

    void WindowManager::Tick(Timestep ts)
    {
        m_Window->OnUpdate();
    }

    void WindowManager::OnEvent(Event& event)
    {
        
    }
}