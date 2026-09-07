#include "WiimoteDevice.hpp"
#include "Data.hpp"

#include <cassert>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	bool WiimoteDevice::checkMotionSampleUpdate(RawMotionSample *retSample) {
		assert(m_native != nullptr);
		assert(this->isConnected());
		assert(WIIUSE_USING_ACC(m_native));

		if (m_native->event == WIIUSE_EVENT) {
			retSample->inited = 1;
			retSample->gforce = m_native->gforce;
			if (m_native->exp.type == EXP_MOTION_PLUS || m_native->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
				retSample->hasMotionPlus = 1;
				if (m_native->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
					retSample->hasNunchuk = 1;
				}
				retSample->gyro = m_native->exp.mp.angle_rate_gyro;
			}
			return 1;
		}
		return 0;
	}
} // namespace wiiviz::Wiimote
