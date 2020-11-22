#include "SandboxApp.h"
#include "GECore/Core.h"
namespace Rocket
{
    class SimpleSandbox : public Application
    {
    public:
        SimpleSandbox()
        {
            RK_INFO("Build Type: {0}", BUILD_TYPE);
            RK_INFO("Source Dir: {0}", ProjectSourceDir);
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
