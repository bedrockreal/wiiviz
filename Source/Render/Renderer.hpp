#pragma once

#include "GridRenderer.hpp"
#include "SceneView.hpp"
#include "WiimoteRenderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct Renderer {
	public:
		Renderer() {}

		bool init() {
			glEnable(GL_DEPTH_TEST);

			bool ok = 1;
			ok &= m_gridRenderer.init();
			ok &= m_wiimoteRenderer.init();
			return ok;
		}
		void shutdown() {}

		void beginFrame();

		void renderScene(const SceneView *scene);
		void endFrame() {}

		void resize(int framebufferWidth, int framebufferHeight);
		void setClearColor(float r, float g, float b, float a) {
			glClearColor(r, g, b, a);
		}
	private:
		void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
		void updateViewport() { glViewport(0, 0, m_viewportWidth, m_viewportHeight); }

		int m_viewportWidth = 0;
		int m_viewportHeight = 0;

		GridRenderer m_gridRenderer;
		WiimoteRenderer m_wiimoteRenderer;
	};
} // namespace wiiviz
