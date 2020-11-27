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

            float square_vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            };
            uint32_t square_indices[] = { 0, 1, 2, 2, 3, 0 };
            {
                m_SquareVertexArray = VertexArray::Create();
                m_SquareVertexArray->Bind();

                auto vertexBuffer_s = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
                vertexBuffer_s->SetLayout({
                    { Rocket::ShaderDataType::Float3, "a_Position" },
                    { Rocket::ShaderDataType::Float2, "a_TexCoord" }
                    });
                m_SquareVertexArray->AddVertexBuffer(vertexBuffer_s);

                auto indexBuffer_s = IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
                m_SquareVertexArray->SetIndexBuffer(indexBuffer_s);
            }

            float cube_vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
            };
            unsigned int cube_indices[] = {
                 0,  1,  2,  3,  4,  5,
                 6,  7,  8,  9, 10, 11,
                12, 13, 14, 15, 16, 17,
                18, 19, 20, 21, 22, 23,
                24, 25, 26, 27, 28, 29,
                30, 31, 32, 33, 34, 35,
            };
            {
                m_CubeVertexArray = VertexArray::Create();
                m_CubeVertexArray->Bind();

                auto vertexBuffer_s = VertexBuffer::Create(cube_vertices, sizeof(cube_vertices));
                vertexBuffer_s->SetLayout({
                    { Rocket::ShaderDataType::Float3, "a_Position" },
                    { Rocket::ShaderDataType::Float2, "a_TexCoord" }
                    });
                m_CubeVertexArray->AddVertexBuffer(vertexBuffer_s);

                auto indexBuffer_s = IndexBuffer::Create(cube_indices, sizeof(cube_indices) / sizeof(uint32_t));
                m_CubeVertexArray->SetIndexBuffer(indexBuffer_s);
            }

            std::string shader_path_1 = ProjectSourceDir + "/Sandbox/assets/shaders/SimpleShader.glsl";
            std::string shader_path_2 = ProjectSourceDir + "/Sandbox/assets/shaders/ColorShader.glsl";
            m_SimpleShader = Shader::Create(shader_path_1);
            m_ColorShader = Shader::Create(shader_path_2);

            std::string img_path_1 = ProjectSourceDir + "/Sandbox/assets/textures/girl_1.jpeg";
            std::string img_path_2 = ProjectSourceDir + "/Sandbox/assets/textures/girl_2.jpeg";
            m_Texture_1 = Texture2D::Create(img_path_1);
            m_Texture_2 = Texture2D::Create(img_path_2);

            m_Camera.reset(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
            static_cast<OrthographicCamera*>(m_Camera.get())->SetPosition(m_Position);
            static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(m_Angle);
        }

        void UpdateCamera(Timestep ts)
        {
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
        }

        void OnUpdate(Timestep ts) override
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            UpdateCamera(ts);

            Renderer::BeginScene(m_Camera);
            {
                glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
                m_ColorShader->Bind();
                m_ColorShader->SetInt("u_Texture", 0);
                m_ColorShader->SetFloat3("u_Color", m_SquareColor);
                m_Texture_1->Bind();
                for (int y = 0; y < 20; y++)
                {
                    for (int x = 0; x < 20; x++)
                    {
                        glm::vec3 pos(x * 0.51f, y * 0.51f, 0.0f);
                        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                        Renderer::Submit(m_ColorShader, m_SquareVertexArray, transform);
                    }
                }
            }
            {
                m_Texture_2->Bind();
                glm::vec3 pos(0.0f, 0.0f, -1.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
                transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                Renderer::Submit(m_ColorShader, m_CubeVertexArray, transform);
            }
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

        Ref<VertexArray> m_CubeVertexArray;

        Ref<Texture2D> m_Texture_1;
        Ref<Texture2D> m_Texture_2;
        
        Ref<OrthographicCamera> m_Camera;
        float m_Angle = 0.0f;
        float m_RotationSpeed = 10.0f;
        float m_MoveSpeed = 1.0f;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    };
}
