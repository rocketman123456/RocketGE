#pragma once
#include "GERender/Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Eigen/Eigen>

namespace Rocket
{
	class OpenGLShader : implements Shader
	{
	public:
		OpenGLShader(const std::string &filepath);
		OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string &name, int value) override;
		virtual void SetIntArray(const std::string &name, int *values, uint32_t count) override;
		virtual void SetFloat(const std::string &name, float value) override;
		virtual void SetFloat2(const std::string &name, const glm::vec2 &value) override;
		virtual void SetFloat3(const std::string &name, const glm::vec3 &value) override;
		virtual void SetFloat4(const std::string &name, const glm::vec4 &value) override;
		virtual void SetMat3(const std::string &name, const glm::mat3 &value) override;
		virtual void SetMat4(const std::string &name, const glm::mat4 &value) override;

		void UploadUniformInt(const std::string &name, int value);
		void UploadUniformIntArray(const std::string &name, int *values, uint32_t count);

		void UploadUniformFloat(const std::string &name, float value);
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);
		void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

		void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

		virtual const std::string &GetName() const override { return m_Name; }
		//--------------------------------------------------------------------------------------
		virtual void SetFloat2Eigen(const std::string &name, const Eigen::Vector2f &value);
		virtual void SetFloat3Eigen(const std::string &name, const Eigen::Vector3f &value);
		virtual void SetFloat4Eigen(const std::string &name, const Eigen::Vector4f &value);
		virtual void SetMat3Eigen(const std::string &name, const Eigen::Matrix3f &value);
		virtual void SetMat4Eigen(const std::string &name, const Eigen::Matrix4f &value);

		void UploadUniformFloat2Eigen(const std::string &name, const Eigen::Vector2f &value);
		void UploadUniformFloat3Eigen(const std::string &name, const Eigen::Vector3f &value);
		void UploadUniformFloat4Eigen(const std::string &name, const Eigen::Vector4f &value);
		void UploadUniformMat3Eigen(const std::string &name, const Eigen::Matrix3f &matrix);
		void UploadUniformMat4Eigen(const std::string &name, const Eigen::Matrix4f &matrix);

	private:
		std::string ReadFile(const std::string &filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
		void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
} // namespace Rocket