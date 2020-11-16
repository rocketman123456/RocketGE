#include "GEBase/EntryPoint.h"
#include "GEBase/Application.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_WARN("Initialize Log");
    
    auto app = Rocket::CreateApplication();
    app->Run();
    delete app;
    return 0;
}