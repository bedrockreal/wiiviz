#pragma once

#include "Camera.hpp"
#include <Core/Input/InputState.hpp>

namespace wiiviz {
	class CameraController {
	public:
		void updateCamera(const InputState *inputState, Camera *camera) {
			if (inputState->middleMouse) {
				if (inputState->shift) {
					camera->pan(inputState->mouseDelta * panSensitivity);
				} else {
					camera->orbit(inputState->mouseDelta * orbitSensitivity);
				}
			}
		}

		void setPanSensitivity(float value) { panSensitivity = value; }
		void setOrbitSensitivity(float value) { orbitSensitivity = value; }
		void setZoomSensitivity(float value) { zoomSensitivity = value; }
		
	private:
		float panSensitivity = 0.01;
		float orbitSensitivity = 0.01;
		float zoomSensitivity = 0.1;
	};
} // namespace wiiviz
