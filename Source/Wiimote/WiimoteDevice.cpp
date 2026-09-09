#include "WiimoteDevice.hpp"
#include "Data.hpp"

#include <cassert>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	bool WiimoteDevice::checkMotionSampleUpdate(RawMotionSample *retSample) {
		assert(m_native != nullptr);
		assert(this->isConnected());
		assert(WIIUSE_USING_ACC(m_native));

		retSample->hasMotionPlus = (m_native->exp.type == EXP_MOTION_PLUS || m_native->exp.type == EXP_MOTION_PLUS_NUNCHUK);
		retSample->hasNunchuk = (m_native->exp.type == EXP_NUNCHUK || m_native->exp.type == EXP_MOTION_PLUS_NUNCHUK);

		if (m_native->event == WIIUSE_EVENT) {
			retSample->inited = 1;
			memcpy(&retSample->gforce, &m_native->gforce, sizeof(gforce_t));
			// assert(m_native->exp.type == EXP_MOTION_PLUS);

			if (retSample->hasMotionPlus) {
				memcpy(&retSample->gyro, &m_native->exp.mp.angle_rate_gyro, sizeof(ang3f_t));
			}
			return 1;
		}
		return 0;
	}
} // namespace wiiviz::Wiimote
