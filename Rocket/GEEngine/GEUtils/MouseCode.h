#pragma once

#include "GECore/Basic.h"

namespace Rocket
{
	// TODO: add keycode convert between different platform
	using MouseCode = int32_t;
	static MouseCode GLFWToRK_Mouse(int32_t key) { return key; }
	static int32_t RKToGLFW_Mouse(MouseCode key) { return key; }

	namespace Mouse
	{
		enum : MouseCode
		{
			Unknown				   = -1,
			// From glfw3.h
			Button0                = 0,
			Button1                = 1,
			Button2                = 2,
			Button3                = 3,
			Button4                = 4,
			Button5                = 5,
			Button6                = 6,
			Button7                = 7,

			ButtonLast             = Button7,
			ButtonLeft             = Button0,
			ButtonRight            = Button1,
			ButtonMiddle           = Button2
		};
	}
}