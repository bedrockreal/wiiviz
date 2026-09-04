#pragma once

#include <Common/ThreadSafeQueue.hpp>

#include <ctime>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	struct RawMotionSample {
		timespec time;
		const gforce_t *gforce = nullptr;
		const ang3f_t *gyro = nullptr;
	};
	typedef wiiviz::ThreadSafeQueue<RawMotionSample> MotionSampleQueue;
} // namespace wiiviz::Wiimote
