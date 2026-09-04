#pragma once

// #include <Common/Singleton.hpp>

#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

namespace wiiviz {
	struct Camera {
		// friend class Singleton<Camera>;
		public:
		Camera();
		void pan(const float dx, const float dy);
		void orbit(const float dx, const float dy);

		// make zoom, getTarget and getView inline
		void zoom(const float offset) {
			pos += direction * offset * zoomSpeed;
		}
		glm::vec3 getTarget() {
			return pos + direction * targetDistance;
		}
		glm::mat4 getView() {
			return glm::lookAt(pos, getTarget(), up);
		}
		void reset();

		private:
		constexpr static glm::vec3 up = glm::vec3(0.f, 0.f, 1.f);
		float targetDistance;

		constexpr static float panSpeed = 0.01;
		constexpr static float orbitSpeed = 0.01;
		constexpr static float zoomSpeed = 0.5;
		constexpr static float maxPitch = glm::radians(89.f);

		// yaw and pitch are in radians.
		// force camera to be upright; roll == 0
		float yaw;
		float pitch;

		glm::vec3 pos;
		glm::vec3 direction;

		void printPos() {
			printf("%.3f %.3f %.3f\n", pos.x, pos.y, pos.z);
		}
	};
} // namespace wiiviz
