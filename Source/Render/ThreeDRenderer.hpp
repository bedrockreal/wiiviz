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
		Camera * getCamera() {
			return &camera;
		}
	private:
		Camera camera;

		glm::mat4 view;
		glm::mat4 projection;

		constexpr static struct {
			float fov;
			float nearZ;
			float farZ;
		} projectionParams = {
			.fov = glm::radians(45.f),
			.nearZ = 0.1f,
			.farZ = 100.f,
		};
	};
} // namespace wiiviz
