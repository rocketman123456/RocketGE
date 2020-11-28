#pragma once
#include "RKEngine.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float vertices[9];
extern uint32_t indices[3];
extern float square_vertices[20];
extern uint32_t square_indices[6];
extern float cube_vertices[180];
extern uint32_t cube_indices[36];

namespace Rocket
{
    class ExampleLayer : implements Layer
    {
    public:
        ExampleLayer() : Layer("ExampleLayer")
        {
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
                    { Rocket::ShaderDataType::Float3, "a_Position" },
                    { Rocket::ShaderDataType::Float2, "a_TexCoord" }
                    });
                m_SquareVertexArray->AddVertexBuffer(vertexBuffer_s);

                auto indexBuffer_s = IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
                m_SquareVertexArray->SetIndexBuffer(indexBuffer_s);
            }
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

            std::string shader_path_1 = ProjectSourceDir + "/Assets/shaders/SimpleShader.glsl";
            std::string shader_path_2 = ProjectSourceDir + "/Assets/shaders/ColorShader.glsl";
            std::string img_path_1 = ProjectSourceDir + "/Assets/textures/wall.jpg";
            std::string img_path_2 = ProjectSourceDir + "/Assets/textures/container.jpg";

            m_ShaderLibrary = ShaderLibrary::Create();
            m_ShaderLibrary->Load("SimpleShader", shader_path_1);
            m_ShaderLibrary->Load("ColorShader", shader_path_2);

            m_Texture_1 = Texture2D::Create(img_path_1);
            m_Texture_2 = Texture2D::Create(img_path_2);

            m_Controller.reset(new OrthographicCameraController(16.0f / 9.0f, true));
            //m_Controller.reset(new PerspectiveCameraController(16.0f / 9.0f));
        }

        void UpdateCamera(Timestep ts)
        {
            m_Controller->OnUpdate(ts);
        }

        void RenderSquare()
        {
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
            auto shader = m_ShaderLibrary->Get("ColorShader");
            shader->Bind();
            shader->SetInt("u_Texture", 0);
            shader->SetFloat3("u_Color", m_SquareColor);
            for (int y = 0; y < 20; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    glm::vec3 pos(x * 0.51f, y * 0.51f, -0.5f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                    Renderer::Submit(shader, m_SquareVertexArray, m_Texture_1, transform);
                }
            }
        }

        void RenderCube()
        {
            glm::vec3 pos(0.0f, 0.0f, -1.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
            transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            Renderer::Submit(m_ShaderLibrary->Get("SimpleShader"), m_CubeVertexArray, m_Texture_2, transform);
        }

        void OnUpdate(Timestep ts) override
        {
            //RK_TRACE("Time {0}", ts);
            UpdateCamera(ts);
            
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene(m_Controller->GetCamera());
            
            if(m_ShowSquare)
                RenderSquare();
            if(m_ShowCube)
                RenderCube();
            
            Renderer::EndScene();
        }

        void OnGuiRender() override
        {
            ImGui::Begin("Example");
            ImGui::Text("Hello Example!");
		    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
            ImGui::Checkbox("Show Square", &m_ShowSquare);
            ImGui::Checkbox("Show Cube", &m_ShowCube);
		    ImGui::End();
        }

        void OnEvent(Event &event) override
        {
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<KeyPressedEvent>(RK_BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
            m_Controller->OnEvent(event);
        }

        bool OnKeyPressed(KeyPressedEvent& event)
        {
            RK_TRACE("KeyCode {0} Key Pressed", event.GetKeyCode());
            return false;
        }
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
