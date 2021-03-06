#pragma once

#include "GECore/Core.h"

namespace Rocket
{
	Interface GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Destory() = 0;

		static Scope<GraphicsContext> Create(void *window);
	};
} // namespace Rocket