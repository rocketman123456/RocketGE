#include "GERender/Shader.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLShader.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanShader.h"
#elif defined(RK_METAL)
#include "GERender/MetalShader.h"
#endif

namespace Rocket {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
			case RenderAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
#elif defined(RK_VULKAN)
			case RenderAPI::API::OpenGL:  return CreateRef<VulkanShader>(filepath);
#elif defined(RK_METAL)
			case RenderAPI::API::OpenGL:  return CreateRef<MetalShader>(filepath);
#endif
		}

		RK_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
			case RenderAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
#elif defined(RK_VULKAN)
			case RenderAPI::API::OpenGL:  return CreateRef<VulkanShader>(name, vertexSrc, fragmentSrc);
#elif defined(RK_METAL)
			case RenderAPI::API::OpenGL:  return CreateRef<MetalShader>(name, vertexSrc, fragmentSrc);
#endif
		}

		RK_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		RK_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		RK_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}