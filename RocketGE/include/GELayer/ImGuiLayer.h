#pragma once

#include "GELayer/Layer.h"

namespace Rocket
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() {}

        void Begin();
        void End();

        void SetDarkThemeColors();
        void BlockEvents(bool block) { m_BlockEvents = block; }
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
} // namespace Rocket
