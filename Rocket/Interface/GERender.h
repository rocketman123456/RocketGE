#pragma once

#include "GERender/Renderer.h"
#include "GERender/RenderAPI.h"
#include "GERender/RenderCommand.h"
#include "GERender/GraphicsContext.h"
#include "GERender/Shader.h"
#include "GERender/Buffer.h"
#include "GERender/VertexArray.h"
#include "GERender/Texture.h"

#if defined(RK_OPENGL)
#include "GERender/OpenGLShader.h"
#include "GERender/OpenGLContext.h"
#elif defined(RK_VULKAN)
#include "GERender/VukanShader.h"
#include "GERender/VulkanContext.h"
#elif defined(RK_METAL)
#include "GERender/MetalShader.h"
#include "GERender/MetalContext.h"
#endif