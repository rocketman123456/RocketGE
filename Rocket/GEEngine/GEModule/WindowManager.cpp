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

    int WindowManager::Tick(Timestep ts)
    {
        m_Window->OnUpdate();
        return 0;
    }

    void WindowManager::OnEvent(Event& event)
    {
        
    }
}