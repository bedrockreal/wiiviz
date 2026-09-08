#pragma once

#include <cstdint>
#include <glm/ext/quaternion_float.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace wiiviz {
	struct DeviceInfo {
		int id = -1;
		bool connected = false;
		bool streaming = false;
		const char *name = "Unknown";
		float battery = 0.0f;
		double sampleRateHz = 0.0;
		std::uint64_t receivedSamples = 0;
		std::uint64_t droppedSamples = 0;
	};

	struct DeviceState {
		bool scanInProgress = false;
		const char *lastError;
		std::vector<DeviceInfo> devices;
	};

	struct MotionSettings {
		float accelSmoothingAlpha = 0.2f;
		float gravityAlpha = 0.05f;
		float complementaryBeta = 0.98f;
		bool integratePosition = false;
	};

	struct MotionDeviceState {
		int id = -1;
		bool valid = false;
		glm::vec3 accelFiltered{0.0f};
		glm::vec3 gravityEstimate{0.0f};
		glm::vec3 linearAcceleration{0.0f};
		glm::vec3 gyroDps{0.0f};
		glm::quat orientation{1.0f, 0.0f, 0.0f, 0.0f};
		glm::vec3 eulerDegrees{0.0f};
		glm::vec3 position{0.0f};
		std::vector<glm::vec3> trailPoints;
	};

	struct MotionState {
		MotionSettings settings;
		std::vector<MotionDeviceState> devices;
	};

	struct CameraState {
		glm::vec3 target{0.0f};
		float distance = 4.0f;
		float yawDegrees = 45.0f;
		float pitchDegrees = 20.0f;
		float fovDegrees = 60.0f;
		float nearPlane = 0.01f;
		float farPlane = 100.0f;
		int viewportWidth = 1280;
		int viewportHeight = 720;
	};

	struct RenderState {
		bool showGrid = true;
		bool showWorldAxes = true;
		bool showDeviceAxes = true;
		bool showTrails = true;
		bool showAccelVector = false;
		bool showGravityVector = true;
		bool showLinearAccelVector = false;
		float gizmoScale = 0.25f;
		float trailWidth = 2.0f;
		glm::vec4 clearColor{0.08f, 0.09f, 0.11f, 1.0f};
	};

	struct UiState {
		int selectedDeviceId = 0;
		bool showDevicePanel = true;
		bool showMotionPanel = true;
		bool showRenderPanel = true;
		bool showLogPanel = true;
	};

	struct SessionState {
		bool paused = false;
		double currentTimeSeconds = 0.0;
		double deltaSeconds = 0.0;
		std::uint64_t frameIndex = 0;
	};

	struct AppState {
		DeviceState devices;
		MotionState motion;
		CameraState camera;
		RenderState render;
		UiState ui;
		SessionState session;
	};
} // namespace wiiviz
