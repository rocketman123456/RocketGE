#pragma once
#include "RKEngine.h"

namespace Rocket {
    class Sandbox2D : implements Application
    {
    public:
        Sandbox2D();
        virtual ~Sandbox2D();
    };

    class Sandbox2DLayer : implements Layer
    {
    public:
        Sandbox2DLayer();
        virtual ~Sandbox2DLayer() = default;

        virtual void OnAttach() override;
		virtual void OnDetach() override;

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnGuiRender() override;
        virtual void OnEvent(Event &event) override;
    private:
        Ref<CameraController> m_Controller;

        glm::vec3 m_SquareColor = { 1.0f, 0.5f, 0.2f };
    };
}