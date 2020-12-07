#pragma once

#include "GECore/Core.h"
#include "GEEvent/Event.h"
#include "GEUtils/Timestep.h"

namespace Rocket {
    Interface Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;
		// Common Function
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		// GUI Related Function
		virtual void OnGuiRender() {}
		virtual void Begin() {}
		virtual void End() {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
