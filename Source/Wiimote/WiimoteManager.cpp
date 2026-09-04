#include "WiimoteManager.hpp"
#include "Data.hpp"
#include <cassert>
#include <functional>

namespace wiiviz::Wiimote {
	WiimoteManager::WiimoteManager() {}
	WiimoteManager::~WiimoteManager() { shutdown(); }
	bool WiimoteManager::init(int capacity) {
		m_devices.resize(capacity);
		m_context = new WiiuseContext(capacity);
		assert(m_context != nullptr);
		return m_context->init();
	}
	void WiimoteManager::shutdown() {
		if (m_context != nullptr) {
			delete m_context;
			m_context = nullptr;
		}
	}

	void WiimoteManager::pollAndUpdate(std::function<void(int, const RawMotionSample*)> onUpdate) {
		if (m_context->poll()) {
			RawMotionSample s;
			for (int i = 0; i < m_devices.size(); ++i) {
				// rebind first (important!)
				// printf("rebind %d\n", i);
				m_devices[i].rebind(i, m_context->getHandleAt(i));

				// check actual update
				bool hasUpdate = m_devices[i].checkMotionSampleUpdate(&s);
				if (hasUpdate) {
					s.time = m_context->getLastPollTime();
					onUpdate(i, &s);
				}
			}
		}
	}
} // namespace wiiviz::Wiimote
