#include "GECore/EntryPoint.h"
#include "GEUtils/Instrumentor.h"

int main(int argc, char **argv)
{
    Rocket::Log::Init();
    RK_CORE_WARN("Initialize Log");
    
    RK_PROFILE_BEGIN_SESSION("Startup", "Profile-Startup.json");
    auto app = Rocket::CreateApplication();
    RK_PROFILE_END_SESSION();

	RK_PROFILE_BEGIN_SESSION("Runtime", "Profile-Runtime.json");
	app->Run();
	RK_PROFILE_END_SESSION();

	RK_PROFILE_BEGIN_SESSION("Shutdown", "Profile-Shutdown.json");
	delete app;
	RK_PROFILE_END_SESSION();
    return 0;
}