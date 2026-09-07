#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace wiiviz {
	struct RenderContext {
		glm::mat4 view;
		glm::mat4 proj;
		glm::mat4 viewProj;
		glm::vec3 cameraPosition;
	};
} // namespace wiiviz
