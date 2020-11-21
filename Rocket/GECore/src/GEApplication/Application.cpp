#include "GEApplication/Application.h"
#include <glad/glad.h>

std::string vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
std::string fragmentShaderSource = R"(
#version 330 core
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

        m_GuiLayer = new ImGuiLayer();
        PushOverlay(m_GuiLayer);

        //Shader::Create("Simple Shader", vertexShaderSource, fragmentShaderSource);
        m_SimpleShader.reset(new OpenGLShader("Simple Shader", vertexShaderSource, fragmentShaderSource));

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
        unsigned int indices[3] = {0, 1, 2};

        glGenVertexArrays(1, &m_VertexArray);
        glGenBuffers(1, &m_VertexBuffer);
        glGenBuffers(1, &m_IndexBuffer);

        glBindVertexArray(m_VertexArray);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event &e)
    {
        //RK_CORE_TRACE(e);
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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_SimpleShader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
        return false;
    }
} // namespace Rocket
