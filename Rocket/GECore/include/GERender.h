#pragma once

#include "GERender/RenderAPI.h"
#include "GERender/GraphicsContext.h"
#include "GERender/Shader.h"

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