#pragma once

#include "Camera.hpp"
#include <Core/Input/InputState.hpp>

namespace wiiviz {
	class CameraController {
	public:
		void updateCamera(const InputState *inputState, Camera *camera) {
			if (inputState->middleMouse) {
				if (inputState->shift) {
					camera->pan(inputState->mouseDelta * m_panSensitivity);
				} else {
					camera->orbit(inputState->mouseDelta * m_orbitSensitivity);
				}
			}
			if (inputState->scrollDelta.y) {
				camera->zoom(inputState->scrollDelta.y * m_zoomSensitivity);
			}
		}

		void setPanSensitivity(float value) { m_panSensitivity = value; }
		void setOrbitSensitivity(float value) { m_orbitSensitivity = value; }
		void setZoomSensitivity(float value) { m_zoomSensitivity = value; }
		
	private:
		float m_panSensitivity = 0.01;
		float m_orbitSensitivity = 0.01;
		float m_zoomSensitivity = 0.1;
	};
} // namespace wiiviz
