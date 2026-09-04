#pragma once

#include "Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct Renderer {
	public:
		virtual void init(GLFWwindow *_window) = 0;
		virtual void shutdown() = 0;

		virtual void useShader(Shader *shader) = 0;

		virtual void beginFrame() = 0;

		virtual void renderScene() = 0;
		void endFrame() {
			glfwSwapBuffers(window);
		}
	protected:
		GLFWwindow *window;
		Shader *activeShader;
	};
} // namespace wiiviz
