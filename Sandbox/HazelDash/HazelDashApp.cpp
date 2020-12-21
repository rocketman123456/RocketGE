#include "RocketDashLayer.h"
#include "Random.h"

#include "RKEngine.h"
#include "GEModule/Application.h"
#include "GECore/EntryPoint.h"

class RocketDashApp : public Rocket::Application
{
public:
	RocketDashApp() : Application("RocketDashApp") {}

	virtual void PreInitialize() override
	{
		Random::Init();
		PushLayer(new RocketDashLayer());
	}

	virtual void PostInitialize() override
	{
	}

	virtual void PreInitializeModule() override
	{
		RK_INFO("Build Type: {0}", BUILD_TYPE);
		RK_INFO("Source Dir: {0}", ProjectSourceDir);

		PushModule(g_ProcessManager);
		PushModule(g_WindowManager);
		PushModule(g_AudioManager);
	}

	virtual void PostInitializeModule() override
	{
	}
};

Rocket::Application *Rocket::CreateApplication()
{
	return new RocketDashApp();
}
