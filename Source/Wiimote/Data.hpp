#pragma once

#include <Common/ThreadSafeQueue.hpp>

#include <ctime>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	struct RawMotionSample {
		// you can't use pointers for gforce and gyro;
		// otherwise the value would change whenever the wiimote_t updates
		// (can't do recording)
		timespec time;
		bool hasMotionPlus = false;
		bool hasNunchuk = false;
		bool inited = false;
		gforce_t gforce;
		ang3f_t gyro;
	};

	typedef wiiviz::ThreadSafeQueue<RawMotionSample> MotionSampleQueue;
} // namespace wiiviz::Wiimote
