#pragma once

#include "Data.hpp"
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	class WiimoteDevice {
	public:
		WiimoteDevice() = default;
		WiimoteDevice(int slotIndex, wiimote_t* native) { rebind(slotIndex, native); }

		void rebind(int slotIndex, wiimote_t* native) {
			m_slotIndex = slotIndex;
			m_native = native;
		}
		bool checkMotionSampleUpdate(RawMotionSample *retSample);

		int getSlotIndex() const { return m_slotIndex; }
		const wiimote_t* getNativeHandle() const { return m_native; }
		// const WiimoteState& state() const { return m_state; }

		bool isValid() const { return m_native != nullptr; }
		bool isConnected() const { return WIIMOTE_IS_CONNECTED(m_native); }

		// void setRumble(bool enabled);
		// void setLedMask(int mask);

	private:
		// void updateConnectionState();
		// void updateButtons();
		// void updateAccel();
		// void updateIR();
		// void updateMotionPlus();

	private:
		int m_slotIndex = -1;
		const wiimote_t* m_native = nullptr; // non-owning: the pointer can point to another wiimote_t, but this struct can't modify any of the wiimote_t's data
		// WiimoteState m_state{};
	};
} // namespace wiiviz::Wiimote
