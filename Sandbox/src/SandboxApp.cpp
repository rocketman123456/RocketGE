#include "Sandbox.h"

namespace Rocket
{
    class Sandbox : public Application
    {
    public:
        Sandbox()
        {

        }
        ~Sandbox()
        {

        }
    };

    Application* CreateApplication()
    {
        return static_cast<Application*>(new Sandbox);
    }
}
