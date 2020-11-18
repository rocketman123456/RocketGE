#include "GELayer/ImGuiLayer.h"

#include "GEEvent.h"
#include "GEApplication.h"

#include <imgui.h>
#ifdef RK_OPENGL
#include <backends/imgui_impl_opengl3.h>
#endif
#ifdef RK_VULKAN
#include "backends/imgui_impl_vulkan.h"
#endif
#ifdef RK_METAL
#include "backends/imgui_impl_metal.h"
#endif
#include <backends/imgui_impl_glfw.h>

#include <glfw/glfw3.h>

namespace Rocket {

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
    {
    }

    void ImGuiLayer::OnAttach()
    {
        // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		std::string ttf_path = std::filesystem::current_path().generic_string() + "/Sandbox/assets/fonts/Cousine-Regular.ttf";
		std::string ttf_default = std::filesystem::current_path().generic_string() + "/Sandbox/assets/fonts/Karla-Regular.ttf";
		io.Fonts->AddFontFromFileTTF(ttf_path.c_str(), 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(ttf_default.c_str(), 18.0f);

		io.DisplaySize.x = 800;
		io.DisplaySize.y = 600;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		//SetDarkThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate(Timestep ts)
    {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		auto time = (float)glfwGetTime();
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& e)
    {
        if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
    }

    void ImGuiLayer::Begin()
    {

    }

    void ImGuiLayer::End()
    {

    }
}