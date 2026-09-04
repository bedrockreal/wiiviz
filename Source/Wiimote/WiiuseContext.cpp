#include "WiiuseContext.hpp"
#include <wiiuse.h>

using namespace wiiviz::Wiimote;

WiiuseContext::WiiuseContext(int capacity)
	: m_capacity(capacity) {}

WiiuseContext::~WiiuseContext() {
    shutdown();
}

bool WiiuseContext::init() {
	if (m_inited) {
		return 1;
	}

	m_wiimotes = wiiuse_init(m_capacity);
	return m_inited = (m_wiimotes != nullptr);
}

void WiiuseContext::shutdown() {
    if (m_wiimotes) {
        wiiuse_cleanup(m_wiimotes, m_capacity);
        m_wiimotes = nullptr;
    }

    m_connectedCount = 0;
    m_inited = false;
}

int WiiuseContext::find(int timeoutSeconds) {
    if (!m_wiimotes) {
        return 0;
    }
    return wiiuse_find(m_wiimotes, m_capacity, timeoutSeconds);
}

int WiiuseContext::connect() {
	if (!m_wiimotes) {
        return 0;
    }
    m_connectedCount = wiiuse_connect(m_wiimotes, m_capacity);

	// temp: for every connected wiimote, activate accelerometer
	for (int i = 0; i < m_capacity; ++i) if (WIIMOTE_IS_CONNECTED(m_wiimotes[i])) {
		puts("activate accel");
		wiiuse_motion_sensing(m_wiimotes[i], 1);
	}
    return m_connectedCount;
}

bool WiiuseContext::poll() {
	if (!m_wiimotes) {
		return 0;
	}
	return wiiuse_poll(m_wiimotes, m_capacity) != 0;
}
