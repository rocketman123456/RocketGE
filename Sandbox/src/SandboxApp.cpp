#include "SandboxApp.h"

namespace Rocket
{
    class SimpleSandbox : public Application
    {
    public:
        SimpleSandbox()
        {

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
