#pragma once

#include "GECore.h"
#include "GEEvent.h"
#include "GEWindow.h"
#include "GELayer.h"
#include "GERender.h"

#include "GERender/Buffer.h"
#include "GERender/VertexArray.h"

namespace Rocket {
    class Application {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Close();

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        void Run();

        inline Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        GuiLayer* m_GuiLayer;
        LayerStack m_LayerStack;
        bool m_Running = true;
        bool m_Minimized = false;
        float m_LastFrameTime = 0.0f;

        Ref<Shader> m_SimpleShader;
        Ref<VertexArray> m_VertexArray;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}