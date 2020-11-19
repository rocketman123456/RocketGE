#pragma once

#include "GECore.h"
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
            if(Input::IsKeyPressed(Key::Tab))
            {
                RK_INFO("Tab Key Pressed");
            }
        }

        void OnEvent(Event &event) override
        {
            if(event.GetEventType() == EventType::KeyPressed)
            {
                RK_TRACE("KeyCode {0} Key Pressed", static_cast<KeyEvent&>(event).GetKeyCode());
            }
        }
    };
} // namespace Rocket