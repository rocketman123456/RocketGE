#pragma once

#include "GERender/Renderer.h"
#include "GERender/RenderAPI.h"
#include "GERender/RenderCommand.h"
#include "GERender/GraphicsContext.h"
#include "GERender/Material.h"
#include "GERender/Shader.h"
#include "GERender/Buffer.h"
#include "GERender/FrameBuffer.h"
#include "GERender/VertexArray.h"
#include "GERender/Texture.h"
#include "GERender/SubTexture2D.h"

#if defined(RK_OPENGL)
#include "GERender/OpenGLShader.h"
#include "GERender/OpenGLTexture2D.h"
#include "GERender/OpenGLContext.h"
#include "GERender/OpenGLBuffer.h"
#include "GERender/OpenGLFrameBuffer.h"
#include "GERender/OpenGLRenderAPI.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanShader.h"
#include "GERender/VulkanTexture2D.h"
#include "GERender/VulkanContext.h"
#include "GERender/VulkanBuffer.h"
#include "GERender/VulkanFrameBuffer.h"
#include "GERender/VulkanRenderAPI.h"
#elif defined(RK_METAL)
#include "GERender/MetalShader.h"
#include "GERender/MetalTexture2D.h"
#include "GERender/MetalContext.h"
#include "GERender/MetalBuffer.h"
#include "GERender/MetalFrameBuffer.h"
#include "GERender/MetalRenderAPI.h"
#endif