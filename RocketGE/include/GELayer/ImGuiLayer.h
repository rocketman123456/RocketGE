#pragma once

#include "GELayer/GuiLayer.h"

namespace Rocket
{
    class ImGuiLayer : public GuiLayer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;

        void Begin();
        void End();

        void SetDarkThemeColors();
        void BlockEvents(bool block) { m_BlockEvents = block; }
    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;
    };
} // namespace Rocket
