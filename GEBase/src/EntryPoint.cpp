#include "GEBase/EntryPoint.h"
#include "GEBase/Application.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_INFO("Initialize Log");
    RK_INFO("Initialize Client");
    
    auto app = Rocket::CreateApplication();
    app->Run();
    delete app;
    return 0;
}