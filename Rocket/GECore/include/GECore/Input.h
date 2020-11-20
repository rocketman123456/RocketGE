#pragma once

#include <glm/glm.hpp>
#include <Eigen/Core>

#include "GECore/KeyCode.h"
#include "GECore/MouseCode.h"

namespace Rocket {
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode key);
		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static Eigen::Vector2f GetMousePositionEigen();
		static float GetMouseX();
		static float GetMouseY();
	};
}