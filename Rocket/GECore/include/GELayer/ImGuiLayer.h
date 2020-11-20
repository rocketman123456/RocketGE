#pragma once

#include "GELayer/GuiLayer.h"

namespace Rocket
{
    class ImGuiLayer : public GuiLayer
    {
    public:
        ImGuiLayer() : GuiLayer("ImGuiLayer") {}
        virtual ~ImGuiLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnGuiRender() override;

        virtual void Begin() override;
        virtual void End() override;

        void SetDarkThemeColors();
        void BlockEvents(bool block) { m_BlockEvents = block; }
    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
} // namespace Rocket
