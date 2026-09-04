#pragma once

#include "Snapshot.hpp"
#include "WiiuseContext.hpp"
#include <atomic>

namespace wiiviz::Wiimote {
	struct Worker {
	public:
		Worker(SharedSnapshot *sharedSnapshotPtr);
		~Worker();
		bool run(int capacity);
		void requestStop();
	private:
		WiiuseContext *m_context = nullptr;
		SharedSnapshot *m_sharedSnapshotPtr = nullptr;
		std::atomic<bool> m_shutdownRequested = 0;
		std::atomic<bool> m_scanRequested = 0;

		void doInit(int capacity);
		void doScan();
		void doConnect();
		void doPublishSnapshot();
	};
} // namespace wiiviz::Wiimote
