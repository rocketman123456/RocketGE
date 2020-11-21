#include "SandboxApp.h"

namespace Rocket
{
    class SimpleSandbox : public Application
    {
    public:
        SimpleSandbox()
        {
            RK_INFO("App Build Type: {0}", BUILD_TYPE);
            RK_INFO("App Source Dir: {0}", ProjectSourceDir);
            PushLayer(new ExampleLayer());
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
