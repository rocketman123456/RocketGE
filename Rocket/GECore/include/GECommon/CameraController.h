#pragma once
#include "GEEvent.h"
#include "GERender/Camera.h"

namespace Rocket {
    enum class CameraControllerType
    {
        None = 0,
        Orthographic,
        Perspective,
    };

    Interface CameraController
    {
    public:
        virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnEvent(Event& e) = 0;
        virtual Camera& GetCamera() = 0;
		virtual const Camera& GetCamera() const = 0;
    };
}
