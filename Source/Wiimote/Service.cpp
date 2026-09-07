#include "Service.hpp"
#include "Snapshot.hpp"
#include "Worker.hpp"
#include <cassert>
#include <thread>

namespace wiiviz::Wiimote {
	void Service::start(int capacity) {
		assert(capacity >= 0);
		// TODO: use std::promise or similar to catch the worker's return value.
		m_sharedSnapshot.reset(capacity);
		m_sharedMotionDataStream.resize(capacity); // TODO: clear the queues
		m_worker = new Worker(&m_sharedSnapshot, m_sharedMotionDataStream.data());
		assert(m_worker != nullptr);
		m_workerThread = std::thread(&Worker::run, m_worker, capacity);
		m_workerThread.detach();
	}

	void Service::stop() {
		m_worker->requestStop();
		if (m_workerThread.joinable()) m_workerThread.join();
		delete m_worker;
	}

	const Snapshot Service::getLatestSnapshot() const {
		return m_sharedSnapshot.read();
	}
} // namespace wiiviz::Wiimote
