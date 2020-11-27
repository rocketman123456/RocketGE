#pragma once
#include "GECore.h"
#include "GEEvent.h"
#include "GELayer.h"
#include "GERender.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
            float square_vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            };
            uint32_t square_indices[] = { 0, 1, 2, 2, 3, 0 };

            {
                m_VertexArray = VertexArray::Create();
                m_VertexArray->Bind();

                auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
                vertexBuffer->SetLayout({
                    { Rocket::ShaderDataType::Float3, "a_Position" }
                    });
                m_VertexArray->AddVertexBuffer(vertexBuffer);

                auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
                m_VertexArray->SetIndexBuffer(indexBuffer);
            }
            {
                m_SquareVertexArray = VertexArray::Create();
                m_SquareVertexArray->Bind();

                auto vertexBuffer_s = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
                vertexBuffer_s->SetLayout({
                    { Rocket::ShaderDataType::Float3, "a_Position" }
                    });
                m_SquareVertexArray->AddVertexBuffer(vertexBuffer_s);

                auto indexBuffer_s = IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
                m_SquareVertexArray->SetIndexBuffer(indexBuffer_s);
            }

            std::string shader_path_1 = ProjectSourceDir + "/Sandbox/assets/shaders/SimpleShader.glsl";
            std::string shader_path_2 = ProjectSourceDir + "/Sandbox/assets/shaders/ColorShader.glsl";
            m_SimpleShader = Shader::Create(shader_path_1);
            m_ColorShader = Shader::Create(shader_path_2);

            std::string img_path = ProjectSourceDir + "/Sandbox/assets/textures/girl.jpeg";
            m_Texture = CreateRef<Texture2D>(Texture2D::Create(img_path));

            m_Camera.reset(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
            m_Position = { 0.0f, 0.0f, 0.0f };
            static_cast<OrthographicCamera*>(m_Camera.get())->SetPosition(m_Position);
            m_Angle = 0.0f;
            static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(m_Angle);
            m_Transform = glm::mat4(1.0f);
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

            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            Renderer::BeginScene(m_Camera);

            m_ColorShader->Bind();
		    m_ColorShader->SetFloat3("u_Color", m_SquareColor);
            for (int y = 0; y < 20; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                    Renderer::Submit(m_ColorShader, m_SquareVertexArray, transform);
                }
            }

            Renderer::Submit(m_SimpleShader, m_VertexArray, m_Transform);

            Renderer::EndScene();
        }

        void OnGuiRender() override
        {
            ImGui::Begin("Example");
            ImGui::Text("Hello Example!");
		    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
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
        Ref<Shader> m_SimpleShader;
        Ref<VertexArray> m_VertexArray;

        Ref<Shader> m_ColorShader;
        Ref<VertexArray> m_SquareVertexArray;
        glm::vec3 m_SquareColor = { 1.0f, 0.5f, 0.2f };
        glm::mat4 m_Transform;

        Ref<Texture2D> m_Texture;
        
        Ref<OrthographicCamera> m_Camera;
        float m_Angle;
        float m_RotationSpeed = 10.0f;
        float m_MoveSpeed = 1.0f;
        glm::vec3 m_Position;
    };
}
