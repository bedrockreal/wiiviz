#pragma once

#include "Camera.hpp"
#include "Renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct ThreeDRenderer : public Renderer {
	public:
		ThreeDRenderer() {}
		ThreeDRenderer(GLFWwindow *_window) {
			init(_window);
		}
		void init(GLFWwindow *_window) override {
			window = _window;
		}
		void shutdown() override {}

		void beginFrame() override;

		void renderScene() override;
		void useShader(Shader *shader) override;
	private:
		glm::mat4 view;
		glm::mat4 projection;
	};
} // namespace wiiviz
