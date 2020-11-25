#pragma once
#include "GECore.h"
#include "GEEvent.h"
#include "GELayer.h"
#include "GERender.h"

#include <imgui.h>

namespace Rocket
{
    class ExampleLayer : public Layer
    {
    public:
        ExampleLayer() : Layer("ExampleLayer")
        {
            float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
            };
            uint32_t indices[] = { 0, 1, 2 };

            m_VertexArray = VertexArray::Create();
            m_VertexArray->Bind();

            auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
            vertexBuffer->SetLayout({
                { Rocket::ShaderDataType::Float3, "a_Position" }
                });
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            m_VertexArray->SetIndexBuffer(indexBuffer);

            std::string shader_path_1 = ProjectSourceDir + "/Sandbox/assets/shaders/SimpleShader.glsl";
            std::string shader_path_2 = ProjectSourceDir + "/Sandbox/assets/shaders/BasicShader.glsl";
            m_SimpleShader = Shader::Create(shader_path_1);
            m_BasicShader = Shader::Create(shader_path_2);

            m_Camera.reset(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
            static_cast<OrthographicCamera*>(m_Camera.get())->SetPosition({ 0.0f, 0.0f, 0.0f });
            static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(45.0f);
        }

        void OnUpdate(Timestep ts) override
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            m_Angle += 1.0f / ts.GetMilliseconds();
            static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(m_Angle);

            Renderer::BeginScene(m_Camera);
            Renderer::Submit(m_SimpleShader, m_VertexArray);
            Renderer::EndScene();
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
                //RK_TRACE("KeyCode {0} Key Pressed", static_cast<KeyEvent&>(event).GetKeyCode());
            }
            else if(event.GetEventType() == EventType::MouseMoved)
            {
                //RK_TRACE("Mouse Pos: {0}, {1}", Input::GetMouseX(), Input::GetMouseY());
            }
        }
    private:
        Ref<Shader> m_SimpleShader, m_BasicShader;
        Ref<VertexArray> m_VertexArray;
        Ref<Camera> m_Camera;
        float m_Angle = 0.0f;
    };
}
