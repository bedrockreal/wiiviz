#pragma once

#include "Snapshot.hpp"
#include "Worker.hpp"

#include <thread>

namespace wiiviz::Wiimote {
	class Service {
	public:
		void start(int capacity);
		void stop();

		// void requestScan();
		// void setRumble(int slot, bool enabled);
		// void setLedMask(int slot, int mask);

		const Snapshot getLatestSnapshot() const;

	private:
		SharedSnapshot m_sharedSnapshot;

		Worker *m_worker;
		std::thread m_workerThread;
		// CommandQueue m_commandQueue;
	};
} // namespace wiiviz::Wiimote
