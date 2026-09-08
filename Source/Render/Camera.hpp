#pragma once

#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct Camera {
	public:
		Camera();
		void pan(const glm::vec2 offset);
		void orbit(const glm::vec2 offset);

		// make zoom, getTarget and getView inline
		void zoom(const float offset) {
			// m_position += direction * offset * zoomSpeed;
		}
		const glm::vec3 getTarget() const {
			return m_position + direction * targetDistance;
		}
		const glm::mat4 getViewMatrix() const {
			return glm::lookAt(m_position, getTarget(), up);
		}
		const glm::mat4 getProjectionMatrix(const float aspectRatio) const {
			return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		}
		const glm::vec3 getPosition() const { return m_position; }
		void reset();

	private:
		constexpr static glm::vec3 up = glm::vec3(0.f, 0.f, 1.f);
		float targetDistance;

		// constexpr static float panSpeed = 0.01;
		// constexpr static float orbitSpeed = 0.01;
		// constexpr static float zoomSpeed = 0.5;
		constexpr static float maxPitch = glm::radians(89.f);

		// yaw and pitch are in radians.
		// force camera to be upright; roll == 0
		float yaw;
		float pitch;

		float fov;
		float nearPlane;
		float farPlane;

		glm::vec3 m_position;
		glm::vec3 direction;

		void printPos() {
			printf("%.3f %.3f %.3f\n", m_position.x, m_position.y, m_position.z);
		}
	};
} // namespace wiiviz
