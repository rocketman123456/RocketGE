#pragma once

#include "GECore/Core.h"
#include "GELayer/Layer.h"

namespace Rocket
{
    class ImGuiLayer : implements Layer
    {
    public:
        ImGuiLayer(bool show_status = true) : Layer("ImGuiLayer"), m_ShowStatus(show_status) {}
        virtual ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
        virtual void OnEvent(Event &event) override;
        virtual void OnGuiRender() override;

        virtual void Begin() override;
        virtual void End() override;

        void SetDarkThemeColors();
        void BlockEvents(bool block) { m_BlockEvents = block; }

    private:
        void RenderStatusTable();

    private:
        bool m_BlockEvents = true;
        bool m_ShowStatus;
        float m_Time = 0.0f;
    };
} // namespace Rocket
