#pragma once

#include "DeviceRenderData.hpp"
#include "RenderContext.hpp"
#include <cstdio>
#include <cstring>
#include <glm/ext/vector_float3.hpp>


namespace wiiviz {
	class WiimoteRenderer {
	public:
		bool init() {
			glGenVertexArrays(1, &m_vao);
			m_shader.loadFromFile("../assets/shaders/main.vs", "../assets/shaders/main.fs");

			glGenBuffers(1, &m_vbo);

			// TODO: remove debug line
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			return 1;
		}
		void shutdown() {}
		void render(const RenderContext *ctx, const DeviceRenderData *device) {
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_shader.bind();

			// TODO: proper wiimote drawing
			glm::vec3 color = device->color;
			glm::vec3 pos = device->position;

			float vertices[] = {
				0.0f, 0.0f, 0.f, color.r, color.g, color.b,
				pos.x, pos.y, pos.z, color.r, color.g, color.b
			};
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			m_shader.setMat4("model", glm::mat4(1.0f));
			m_shader.setMat4("view", ctx->view);
			m_shader.setMat4("projection", ctx->proj);

			glBindVertexArray(m_vao);
			glDrawArrays(GL_LINES, 0, 2);

			m_shader.unbind();
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
	private:
		Shader m_shader;
		GLuint m_vao = 0;
		GLuint m_vbo = 0;

	};
} // namespace wiiviz
