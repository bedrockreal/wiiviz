#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace wiiviz {
	struct DeviceRenderData {
		// for now, keep position and colour only, leave others for the future

		// int slot = -1;
		// bool connected = false;

		glm::vec3 position{0.0f};
		// glm::quat orientation{1.0f, 0.0f, 0.0f, 0.0f};

		// glm::vec3 accel{0.0f};
		// glm::vec3 gravity{0.0f};
		// glm::vec3 linearAccel{0.0f};

		// std::vector<glm::vec3> trail;

		glm::vec4 color{1.0f};
		// bool selected = false;
	};
} // namespace wiiviz
