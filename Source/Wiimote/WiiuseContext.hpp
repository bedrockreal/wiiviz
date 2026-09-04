# pragma once

#include <wiiuse.h>

namespace wiiviz::Wiimote {
	struct WiiuseContext {
	public:
		explicit WiiuseContext(int capacity);
		~WiiuseContext();

		WiiuseContext(const WiiuseContext&) = delete;
		WiiuseContext& operator=(const WiiuseContext&) = delete;

		bool init();
		void shutdown();

		int find(int timeoutSeconds);
		int connect();
		bool poll();

		int capacity() const { return m_capacity; }
		int getConnectedCount() const { return m_connectedCount; }

		wiimote_t** getHandles() { return m_wiimotes; }
		const wiimote_t* const* getHandles() const { return m_wiimotes; }

		wiimote_t* getHandleAt(int index) {
			return (index < 0 || index >= m_capacity) ? nullptr : m_wiimotes[index];
		}
		const wiimote_t* getHandleAt(int index) const {
			return (index < 0 || index >= m_capacity) ? nullptr : m_wiimotes[index];
		}

		const bool isWiimoteConnected(int index) const {
			return (index < 0 || index >= m_capacity) ? 0 : WIIMOTE_IS_CONNECTED(m_wiimotes[index]);
		}


	private:
		wiimote_t **m_wiimotes = nullptr;
		int m_capacity = 0;
		int m_connectedCount = 0;
		bool m_inited = false;
	};
} // namespace wiiviz::Wiimote
