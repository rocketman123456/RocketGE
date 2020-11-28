#pragma once
#include "GEEvent.h"

namespace Rocket {
    Interface CameraController
    {
    public:
        virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnEvent(Event& e) = 0;
    };
}
