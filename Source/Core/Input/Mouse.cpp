#include "Mouse.hpp"

#include <Render/SceneView.hpp>
#include <GLFW/glfw3.h>

extern wiiviz::SceneView scene;

namespace wiiviz::Mouse {
	void cursorCallback(GLFWwindow *window, double xpos, double ypos) {
		double dx = xpos - lastX;
		double dy = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		if (!inited) {
			inited = true;
			return;
		}

		/* Blender-styled control:
		 * MMB -> orbit
		 * shift + MMB -> pan
		 */
		if (cursorAction == ORBIT) {
			scene.camera.orbit(dx, dy);
		} else if (cursorAction == PAN) {
			scene.camera.pan(dx, dy);
		}
	}

	void scrollCallback(GLFWwindow *window, double dx, double dy) {
		scene.camera.zoom(dy);
	}

	void buttonCallback(GLFWwindow* window, int button, int action, int mods) {
		// printf("buttonCallback(button=%d, mods=%d)\n", button, mods);
		if (action == GLFW_PRESS) buttonsHeld |= (1 << button);
		else if (action == GLFW_RELEASE) buttonsHeld &= (buttonsAll - (1 << button));

		if (buttonsHeld & (1 << GLFW_MOUSE_BUTTON_MIDDLE)) {
			cursorAction = ((mods & GLFW_MOD_SHIFT) ? PAN : ORBIT);
		} else {
			cursorAction = NONE;
		}
	}

	void bindCallbacks(GLFWwindow *window) {
		glfwSetMouseButtonCallback(window, buttonCallback);
		glfwSetCursorPosCallback(window, cursorCallback);
		glfwSetScrollCallback(window, scrollCallback);
	}
} // namespace wiiviz::Mouse
