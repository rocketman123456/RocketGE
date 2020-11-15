#include "GEBase.h"

class Sandbox : public Rocket::Application
{
public:
    Sandbox()
    {

    }
    ~Sandbox()
    {

    }
};

int main()
{
    Sandbox *sandbox = new Sandbox();
    sandbox->Run();
    delete sandbox;
    return 0;
}