#pragma once
#include "RKEngine.h"

namespace Rocket {
    class Sandbox2D : implements Application
    {
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;
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

        std::vector<Ref<Texture2D>> m_Texture;

        glm::vec3 m_SquareColor = { 1.0f, 0.5f, 0.2f };
    };
}