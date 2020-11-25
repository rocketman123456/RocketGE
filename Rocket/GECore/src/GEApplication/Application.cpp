#include "GEApplication/Application.h"
#include "GERender/Renderer.h"
#include "GERender/RenderCommand.h"
#include "GERender/OrthographicCamera.h"

std::string vertexShaderSrc = R"(
#version 410 core
layout (location = 0) in vec3 a_Position;
uniform mat4 u_ViewProjection;
void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
)";
std::string fragmentShaderSrc = R"(
#version 410 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";
std::string vertexShaderSrc_1 = R"(
#version 410 core
layout (location = 0) in vec3 a_Position;
uniform mat4 u_ViewProjection;
void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position.x, 1.0);
}
)";
std::string fragmentShaderSrc_1 = R"(
#version 410 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

namespace Rocket
{
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        RK_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create(WindowProps("Rocket Engine", 1280, 720)));
        m_Window->SetEventCallback(RK_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        uint32_t indices[] = {0, 1, 2};

        m_VertexArray = VertexArray::Create();
        m_VertexArray->Bind();

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout({
            { Rocket::ShaderDataType::Float3, "a_Position" }
        });
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SimpleShader = Shader::Create("Simple Shader", vertexShaderSrc, fragmentShaderSrc);
        m_BasicShader = Shader::Create("Basic Shader", vertexShaderSrc, fragmentShaderSrc);

        m_Camera.reset(new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));
        static_cast<OrthographicCamera*>(m_Camera.get())->SetPosition({0.0f, 0.0f, 0.0f});
        static_cast<OrthographicCamera*>(m_Camera.get())->SetRotation(45.0f);

        m_GuiLayer = new ImGuiLayer();
        PushOverlay(m_GuiLayer);
    }

    Application::~Application()
    {
        RK_CORE_INFO("Exit Application");
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(RK_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(RK_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        RK_INFO("Start Application Run Loop");
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene(m_Camera);
            Renderer::Submit(m_SimpleShader, m_VertexArray);
            Renderer::EndScene();

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate(Timestep(0.03));
            }

            m_GuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
            {
                if (dynamic_cast<GuiLayer *>(layer))
                {
                    static_cast<GuiLayer *>(layer)->OnGuiRender();
                }
            }
            m_GuiLayer->End();

            m_Window->OnUpdate();
        }
        RK_INFO("End Application Run Loop");
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}
