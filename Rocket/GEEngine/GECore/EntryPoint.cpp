#include "GECore/EntryPoint.h"
#include "GEUtils/Instrumentor.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_WARN("Initialize Log");
    
    RK_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
    auto app = Rocket::CreateApplication();
    app->PreInitializeModule();
    if(app->InitializeModule() != 0)
        return 1;
    app->PostInitializeModule();

    app->PreInitialize();
    if(app->Initialize() != 0)
        return 1;
    app->PostInitialize();
    RK_PROFILE_END_SESSION();

	RK_PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
    while(app->GetIsRunning())
    {
        app->Tick();
        app->TickModule();
    }
	RK_PROFILE_END_SESSION();

	RK_PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
    app->Finalize();
    app->FinalizeModule();
	delete app;
	RK_PROFILE_END_SESSION();
    return 0;
}