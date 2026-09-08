#pragma once

#include <glm/vec2.hpp>

namespace wiiviz {
	struct MouseButtonState {
		bool down = false;
		bool pressed = false;
		bool released = false;
	};

	struct InputState {
		bool inited = false;
		glm::vec2 mousePos;
		glm::vec2 mouseDelta;
		glm::vec2 scrollDelta;
		// MouseButtonState leftMouse;
		// MouseButtonState rightMouse;
		// MouseButtonState middleMouse;

		bool leftMouse;
		bool rightMouse;
		bool middleMouse;

		bool shift = false;
		bool ctrl = false;
		bool alt = false;

		// bool windowFocused = true;
		// bool mouseCapturedByUi = false;
		// bool keyboardCapturedByUi = false;
	};
} // namespace wiiviz
