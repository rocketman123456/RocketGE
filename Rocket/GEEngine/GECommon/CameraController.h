#pragma once
#include "GEEvent/Event.h"
#include "GECommon/Camera.h"
#include "GEUtils/Timestep.h"

namespace Rocket
{
    enum class CameraControllerType
    {
        None = 0,
        Orthographic,
        Perspective,
    };

    enum class Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Interface CameraController
    {
    public:
        virtual void OnUpdate(Timestep ts) = 0;
        virtual void OnEvent(Event & e) = 0;
        virtual const Camera &GetCamera() const = 0;

        static Ref<CameraController> Create(CameraControllerType type, float aspectRatio);
    };
} // namespace Rocket
