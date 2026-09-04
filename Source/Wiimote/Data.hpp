#pragma once

#include <Common/ThreadSafeQueue.hpp>

#include <wiiuse.h>

namespace wiiviz::Wiimote {
	struct RawMotionSample {
		// double time; // from glfwGetTime()
		gforce_t gforce;
		ang3f_t gyro;
	};
	typedef wiiviz::ThreadSafeQueue<RawMotionSample> MotionData;
} // namespace wiiviz::Wiimote
