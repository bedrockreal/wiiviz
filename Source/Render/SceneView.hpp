#pragma once

#include "Camera.hpp"
#include "DeviceRenderData.hpp"
// #include "RenderSettings.hpp"

namespace wiiviz {
	struct SceneView {
		Camera camera;
		std::vector<DeviceRenderData> devices;
		// RenderSettings settings;
	};
} // wiiviz
