#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace wiiviz::Window {
	constexpr unsigned int SCR_WIDTH = 800;
	constexpr unsigned int SCR_HEIGHT = 600;

	static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	void configure() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef	__APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif
	}

	void bindCallbacks(GLFWwindow *window) {
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	}

	void clearScreen(const float r, const float g, const float b, const float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
} // namespace wiiviz::Window
