#include "GERender/Renderer.h"
#include "GERender/RenderCommand.h"
#include "GERender2D/Renderer2D.h"

namespace Rocket
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height, float xscale, float yscale)
	{
		RenderCommand::SetViewport(0, 0, width, height, xscale, yscale);
	}

	void Renderer::BeginScene(const Ref<Camera> camera)
	{
		s_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::BeginScene(const Camera &camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const Ref<Texture> &texture, const glm::mat4 &transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		texture->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
} // namespace Rocket