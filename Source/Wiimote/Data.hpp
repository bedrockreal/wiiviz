#pragma once

#include <Common/ThreadSafeQueue.hpp>

#include <ctime>
#include <glm/vec3.hpp>

namespace wiiviz::Wiimote {
	struct RawMotionSample {
		// you can't use pointers for gforce and gyro;
		// otherwise the value would change whenever the wiimote_t updates
		// (can't do recording)
		timespec time;
		bool hasMotionPlus = false;
		bool hasNunchuk = false;
		bool inited = false;
		glm::vec3 gforce;
		glm::vec3 gyro;
	};

	typedef wiiviz::ThreadSafeQueue<RawMotionSample> MotionSampleQueue;
} // namespace wiiviz::Wiimote
