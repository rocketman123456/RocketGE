#pragma once
#include "GERender/FrameBuffer.h"

namespace Rocket
{
	class OpenGLFrameBuffer : implements Framebuffer
	{
	public:
		OpenGLFrameBuffer(const FramebufferSpecification &spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }

		virtual const FramebufferSpecification &GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		uint32_t m_DepthStencilAttachment = 0;
		FramebufferSpecification m_Specification;
	};
} // namespace Rocket