#include "GECore/EntryPoint.h"
#include "GEUtils/Instrumentor.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_WARN("Initialize Log");
    
    RK_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
    // TODO : modify init order, use module first
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
	//app->Run();
    while(app->GetIsRunning())
    {
        app->TickModule();
        app->Tick();
    }
	RK_PROFILE_END_SESSION();

	RK_PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
    app->Finalize();
    app->FinalizeModule();
	delete app;
	RK_PROFILE_END_SESSION();
    return 0;
}