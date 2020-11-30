#pragma once
#include "RKEngine.h"

#include <imgui.h>
#include <glm/glm.hpp>

namespace Rocket
{
    class ExampleLayer : implements Layer
    {
    public:
        ExampleLayer();
        virtual ~ExampleLayer() = default;

        void UpdateCamera(Timestep ts);

        void RenderSquare();
        void RenderCube();

        virtual void OnUpdate(Timestep ts) override;
        virtual void OnGuiRender() override;
        virtual void OnEvent(Event &event) override;

        bool OnKeyPressed(KeyPressedEvent& event);
    private:
        Ref<ShaderLibrary> m_ShaderLibrary;

        Ref<VertexArray> m_VertexArray;
        Ref<VertexArray> m_SquareVertexArray;
        Ref<VertexArray> m_CubeVertexArray;

        glm::vec3 m_SquareColor = { 1.0f, 0.5f, 0.2f };

        Ref<Texture2D> m_Texture_1;
        Ref<Texture2D> m_Texture_2;

        bool m_ShowSquare = false;
        bool m_ShowCube = false;
        
        Ref<CameraController> m_Controller;
    };
}
