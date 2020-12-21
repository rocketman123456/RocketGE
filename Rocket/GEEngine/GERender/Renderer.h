#pragma once
#include "GECore/Core.h"
#include "GERender/RenderAPI.h"
#include "GERender/VertexArray.h"
#include "GERender/Texture.h"
#include "GERender/Shader.h"
#include "GECommon/Camera.h"

#include <glm/glm.hpp>
#include <Eigen/Eigen>

namespace Rocket {
    class Renderer
    {
    public:
        static void Init();
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height, float xscale = 1.0f, float yscale = 1.0f);

        static void BeginScene(const Ref<Camera> camera);
		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Ref<Texture>& texture, const glm::mat4& transform = glm::mat4(1.0f));

		static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
    private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			Eigen::Matrix4f ViewProjectionMatrixEigen;
		};

		static Scope<SceneData> s_SceneData;
    };
}