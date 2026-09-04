#pragma once

#include "WiiuseContext.hpp"
#include "WiimoteDevice.hpp"

#include <functional>
#include <vector>

namespace wiiviz::Wiimote {
	class WiimoteManager {
	public:
		WiimoteManager();
		~WiimoteManager();
		bool init(int capacity);
		void shutdown();

		int scan(int timeoutSeconds) { return m_context->find(timeoutSeconds); }
		int connect() { return m_context->connect(); }

		void pollAndUpdate(std::function<void(int, const RawMotionSample*)> onUpdate);

		int getCapacity() const { return m_context->getCapacity(); }
		int getConnectedCount() const { return m_context->getConnectedCount(); }

		// const WiimoteDevice& device(int slot) const;
		// WiimoteDevice& device(int slot);

	private:
		WiiuseContext *m_context = nullptr;
		std::vector<WiimoteDevice> m_devices;
	};
} // namespace wiiviz::Wiimote
