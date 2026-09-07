#pragma once

#include "Camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct Renderer {
	public:
		Renderer() {}

		bool init() { return 1; }
		void shutdown() {}

		void beginFrame();

		void renderScene();
		void endFrame() {}

		void resize(int framebufferWidth, int framebufferHeight);
	private:
		void clear() { glClear(GL_COLOR_BUFFER_BIT); }
		void updateViewport() { glViewport(0, 0, m_viewportWidth, m_viewportHeight); }

		int m_viewportWidth = 0;
		int m_viewportHeight = 0;
	};
} // namespace wiiviz
