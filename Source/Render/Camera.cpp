#include "Camera.hpp"

#include <cmath>
#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

using namespace wiiviz;

Camera::Camera() {
	reset();
}

void Camera::reset() {
	m_position = glm::vec3(1, 1, 1);
	direction = glm::normalize(-m_position); // set target := (0, 0, 0)
	targetDistance = glm::length(m_position);

	fov = glm::radians(45.f);
	nearPlane = 0.01f;
	farPlane = 100.f;
}

void Camera::pan(const float mouse_dx, const float mouse_dy) {
	// printf("pan dx=%.3f dy=%.3f\n", mouse_dx, mouse_dy);
	glm::vec3 right = glm::normalize(glm::cross(up, direction));
	m_position += (right * mouse_dx + up * mouse_dy) * panSpeed;
	// printPos();
}

void Camera::orbit(const float mouse_dx, const float mouse_dy) {
	// printf("orbit dx=%.3f dy=%.3f\n", mouse_dx, mouse_dy);
	const glm::vec3 target = getTarget();
	glm::vec3 directionNeg = glm::normalize(-direction);
	float pitch = std::asinf((directionNeg.z));
	float yaw = std::atan2(directionNeg.y, directionNeg.x);

	yaw -= mouse_dx * orbitSpeed;
	pitch = glm::max(-maxPitch, glm::min(pitch + mouse_dy * orbitSpeed, maxPitch));

	// printf("yaw=%.3f pitch=%.3f\n", yaw, pitch);

	directionNeg.x = std::cosf(pitch) * std::cosf(yaw);
	directionNeg.y = std::cosf(pitch) * std::sinf(yaw);
	directionNeg.z = std::sinf(pitch);

	direction = glm::normalize(-directionNeg);
	m_position = target - direction * targetDistance;
	// printPos();
}
