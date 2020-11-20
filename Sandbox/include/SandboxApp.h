#pragma once

#include "GECore.h"
#include "GEEvent.h"
#include "GELayer.h"

#include <imgui.h>

namespace Rocket
{
    class ExampleLayer : public GuiLayer
    {
    public:
        ExampleLayer() : GuiLayer("ExampleLayer") {}

        void OnUpdate(Timestep ts) override
        {
            if(Input::IsKeyPressed(Key::Tab))
            {
                RK_INFO("Tab Key Pressed");
            }
        }

        void OnGuiRender() override
        {
            ImGui::Begin("Example");
            ImGui::Text("Hello Example!");
            ImGui::End();
        }

        void OnEvent(Event &event) override
        {
            if(event.GetEventType() == EventType::KeyPressed)
            {
                RK_TRACE("KeyCode {0} Key Pressed", static_cast<KeyEvent&>(event).GetKeyCode());
            }
            //else if(event.GetEventType() == EventType::MouseMoved)
            //{
            //    RK_TRACE("Mouse Pos: {0}, {1}", Input::GetMouseX(), Input::GetMouseY());
            //}
        }
    };
} // namespace Rocket