#include "SandboxApp.h"

namespace Rocket
{
    class SimpleSandbox : public Application
    {
    public:
        SimpleSandbox()
        {
            //PushLayer(new ExampleLayer());
            PushOverlay(new ImGuiLayer());
        }
        ~SimpleSandbox()
        {

        }
    };

    Application* CreateApplication()
    {
        return static_cast<Application*>(new SimpleSandbox);
    }
}
