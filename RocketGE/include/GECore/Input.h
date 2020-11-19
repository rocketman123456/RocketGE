#pragma once

#include <glm/glm.hpp>
#include <Eigen/Core>

#include "GECore/KeyCode.h"
#include "GECore/MouseCode.h"

namespace Rocket {
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode key);
		inline static bool IsMouseButtonPressed(MouseCode button);
		inline static glm::vec2 GetMousePosition();
		inline static Eigen::Vector2f GetMousePositionEigen();
		inline static float GetMouseX();
		inline static float GetMouseY();
	};
}