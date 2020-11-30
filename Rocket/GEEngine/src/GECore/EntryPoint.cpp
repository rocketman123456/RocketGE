#include "GECore/EntryPoint.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_WARN("Initialize Log");
    
    auto app = Rocket::CreateApplication();
    app->Run();
    SafeRelease<Rocket::Application>(&app);
    return 0;
}