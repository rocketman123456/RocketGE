#pragma once
#include "GECore/Core.h"
#include "GERender/RenderAPI.h"
#include "GERender/VertexArray.h"
#include "GERender/Shader.h"
#include <glm/glm.hpp>

namespace Rocket {
    class Renderer
    {
    public:
        static void Init();
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene();
		//static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
    private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
    };
}