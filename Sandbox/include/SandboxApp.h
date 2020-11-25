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
            m_Position = { 0.0f, 0.0f, 0.0f };
            static_cast<OrthographicCamera*>(m_Camera.get())->SetPosition(m_Position);
            m_Angle = 0.0f;
            static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(m_Angle);
        }

        void OnUpdate(Timestep ts) override
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            if (Input::IsKeyPressed(Key::Left) || Input::IsKeyPressed(Key::A))
                m_Position.x += m_MoveSpeed * ts;
            if (Input::IsKeyPressed(Key::Right) || Input::IsKeyPressed(Key::D))
                m_Position.x -= m_MoveSpeed * ts;
            if (Input::IsKeyPressed(Key::Up) || Input::IsKeyPressed(Key::W))
                m_Position.y += m_MoveSpeed * ts;
            if (Input::IsKeyPressed(Key::Down) || Input::IsKeyPressed(Key::S))
                m_Position.y -= m_MoveSpeed * ts;
            if (Input::IsKeyPressed(Key::Q))
                m_Angle += m_RotationSpeed * ts;
            if (Input::IsKeyPressed(Key::E))
                m_Angle -= m_RotationSpeed * ts;

            m_Camera->SetPosition(m_Position);
            m_Camera->SetRotation(m_Angle);

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
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<KeyPressedEvent>(RK_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
        }

        bool OnKeyPressed(KeyPressedEvent& event)
        {
            RK_TRACE("KeyCode {0} Key Pressed", event.GetKeyCode());
            return false;
        }
    private:
        Ref<Shader> m_SimpleShader, m_BasicShader;
        Ref<VertexArray> m_VertexArray;
        Ref<OrthographicCamera> m_Camera;
        float m_Angle;
        float m_RotationSpeed = 10.0f;
        float m_MoveSpeed = 1.0f;
        glm::vec3 m_Position;
    };
}
