#include "Sandbox2D.h"

namespace Rocket {
    Application* CreateApplication()
    {
        return static_cast<Application*>(new Sandbox2D);
    }

    Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer")
    {

    }

    Sandbox2DLayer::~Sandbox2DLayer()
    {

    }

    void Sandbox2DLayer::OnAttach()
    {

    }

	void Sandbox2DLayer::OnDetach()
    {

    }

    void Sandbox2DLayer::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        RenderCommand::Clear();
    }

    void Sandbox2DLayer::OnGuiRender()
    {

    }

    void Sandbox2DLayer::OnEvent(Event &event)
    {

    }
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    //------------------------------------------------------------------------
    Sandbox2D::Sandbox2D()
    {
        RK_INFO("Build Type: {0}", BUILD_TYPE);
        RK_INFO("Source Dir: {0}", ProjectSourceDir);
        PushLayer(new Sandbox2DLayer());
    }

    Sandbox2D::~Sandbox2D()
    {

    }
}
