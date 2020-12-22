#include "GELayer/ImGuiLayer.h"
#include "GEModule/Application.h"
#include "GEUtils/Profile.h"

#include <imgui.h>
#ifdef RK_OPENGL
#include <examples/imgui_impl_opengl3.h>
#endif
#ifdef RK_VULKAN
#include "examples/imgui_impl_vulkan.h"
#endif
#ifdef RK_METAL
#include "examples/imgui_impl_metal.h"
#endif
#include <examples/imgui_impl_glfw.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rocket
{
	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		if (1)
		{
			ImGui::StyleColorsDark();
		}
		else
		{
			ImGui::StyleColorsClassic();
		}
		//SetDarkThemeColors();

		ImGuiIO &io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	  // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		std::string ttf_path = ProjectSourceDir + "/Assets/fonts/opensans/OpenSans-Bold.ttf";
		std::string ttf_default = ProjectSourceDir + "/Assets/fonts/opensans/OpenSans-Regular.ttf";
		io.Fonts->AddFontFromFileTTF(ttf_path.c_str(), 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF(ttf_default.c_str(), 18.0f);

		Application &app = Application::Get();
		GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());
		float xscale, yscale;
		glfwGetWindowContentScale(window, &xscale, &yscale);
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		io.DisplayFramebufferScale = ImVec2(xscale, yscale);

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle &style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(Timestep ts)
	{
		ImGuiIO &io = ImGui::GetIO();

		auto time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;
	}

	void ImGuiLayer::OnEvent(Event &e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO &io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategory::EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategory::EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO &io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnGuiRender()
	{
		if (m_ShowStatus)
			RenderStatusTable();
	}

	void ImGuiLayer::RenderStatusTable()
	{
		ImGui::Begin("Profiler");
		ImGui::Columns(5, "Status"); ImGui::Separator();
		ImGui::Text("Ave"); ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 50); ImGui::NextColumn();
		ImGui::Text("Min"); ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 50); ImGui::NextColumn();
		ImGui::Text("Max"); ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 50); ImGui::NextColumn();
		ImGui::Text(" # "); ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 30); ImGui::NextColumn(); 
		ImGui::Text("Profile Name"); ImGui::SetColumnWidth(ImGui::GetColumnIndex(), 400); ImGui::NextColumn();
		ImGui::Separator();
#ifdef RK_DEBUG
		auto info_stack = ProfilerGetInfo();
		for (auto info : info_stack)
		{
			char label[32];

			sprintf(label, "%3.1f", info.fAve);
			ImGui::Text("%s", label);
			ImGui::NextColumn();

			sprintf(label, "%3.1f", info.fMin);
			ImGui::Text("%s", label);
			ImGui::NextColumn();

			sprintf(label, "%3.1f", info.fMax);
			ImGui::Text("%s", label);
			ImGui::NextColumn();

			sprintf(label, "%4d", info.iNum);
			ImGui::Text("%s", label);
			ImGui::NextColumn();

			sprintf(label, "%s", info.szName.c_str());
			ImGui::Text("%s", label);
			ImGui::NextColumn();
		}
#endif
		ImGui::Separator();
		ImGui::End();
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto &colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};

		// Headers
		colors[ImGuiCol_Header] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
		colors[ImGuiCol_HeaderHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
		colors[ImGuiCol_HeaderActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
		colors[ImGuiCol_ButtonHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
		colors[ImGuiCol_ButtonActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
		colors[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
		colors[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
		colors[ImGuiCol_TabHovered] = ImVec4{0.38f, 0.3805f, 0.381f, 1.0f};
		colors[ImGuiCol_TabActive] = ImVec4{0.28f, 0.2805f, 0.281f, 1.0f};
		colors[ImGuiCol_TabUnfocused] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
		colors[ImGuiCol_TitleBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
	}
} // namespace Rocket