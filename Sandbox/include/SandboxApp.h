#pragma once

#include "GEBase.h"
#include "GEEvent.h"
#include "GELayer.h"

namespace Rocket
{
    class ExampleLayer : public Layer
    {
    public:
        ExampleLayer() : Layer("ExampleLayer") {}

        void OnUpdate(Timestep ts) override
        {
            //RK_INFO("ExampleLayer Update");
        }

        void OnEvent(Event &event) override
        {
            RK_TRACE(event);
        }
    };
} // namespace Rocket