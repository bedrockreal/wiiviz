#pragma once

#include "RenderContext.hpp"
#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace wiiviz {
	class GridRenderer {
	public:
		bool init() {
			glGenVertexArrays(1, &m_vao);
			m_shader.loadFromFile("../assets/shaders/grid.vs", "../assets/shaders/grid.fs");
			return 1;
		}
		void shutdown() {
		}
		void render(const RenderContext *ctx) {
			glm::mat4 invViewProj = glm::inverse(ctx->viewProj);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_CULL_FACE);

			m_shader.bind();
			m_shader.setMat4("uInvViewProj", invViewProj);
			m_shader.setVec3("uCameraPos", ctx->cameraPosition);

			m_shader.setFloat1("uMinorScale", 0.1f);
			m_shader.setFloat1("uMajorScale", 1.0f);

			m_shader.setFloat4("uMinorColor", 0.35f, 0.35f, 0.35f, 0.35f);
			m_shader.setFloat4("uMajorColor", 0.55f, 0.55f, 0.55f, 0.75f);
			m_shader.setFloat4("uAxisXColor", 1.0f, 0.2f, 0.2f, 1.0f);
			m_shader.setFloat4("uAxisZColor", 0.2f, 0.4f, 1.0f, 1.0f);

			m_shader.setFloat1("uFadeStart", 5.0f);
			m_shader.setFloat1("uFadeEnd", 5.0f);

			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);

			m_shader.unbind();
		}

	private:
		Shader m_shader;
		GLuint m_vao = 0;
	};
} // namespace wiiviz

