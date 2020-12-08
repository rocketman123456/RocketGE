#include "RKEngine.h"
#include "GameLayer.h"

class SimpleGame : public Rocket::Application
{
public:
    virtual void PostInitialize() override
    {
        PushLayer(new GameLayer());
    }

	SimpleGame() {}
	virtual ~SimpleGame() {}
};

Rocket::Application* Rocket::CreateApplication()
{
	return new SimpleGame();
}