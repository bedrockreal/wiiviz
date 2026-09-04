#pragma once

// #include <Common/Singleton.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace wiiviz::Mouse {
	enum CursorActionEnum { NONE, ORBIT, PAN };
	static CursorActionEnum cursorAction = NONE;
	constexpr static int buttonsAll = (2 << GLFW_MOUSE_BUTTON_LAST) - 1;
	static int buttonsHeld = 0;

	static double lastX = 0;
	static double lastY = 0;
	static bool inited = false;
	void cursorCallback(GLFWwindow *window, double xpos, double ypos);
	void scrollCallback(GLFWwindow *window, double dx, double dy);
	void buttonCallback(GLFWwindow* window, int button, int action, int mods);
	void bindCallbacks(GLFWwindow *window);
} // namespace wiiviz::Mouse
