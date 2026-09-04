#pragma once

#include "Data.hpp"
#include "Snapshot.hpp"
#include "WiimoteManager.hpp"
#include <atomic>

namespace wiiviz::Wiimote {
	// TODO: worker no longer owns WiiuseContext,
	// because we want an independent motion sample queue per wiimote
	// instead, the WiimoteManager owns it and communicates with worker
	struct Worker {
	public:
		Worker(SharedSnapshot *sharedSnapshotPtr, MotionSampleQueue **sharedMotionDataStream);
		~Worker();
		bool run(int capacity);
		void requestStop();
	private:
		WiimoteManager *m_wiimoteManager = nullptr;
		SharedSnapshot *m_sharedSnapshotPtr = nullptr;
		MotionSampleQueue **m_sharedMotionDataStream;
		std::atomic<bool> m_shutdownRequested = 0;
		std::atomic<bool> m_scanRequested = 0;

		void doInit(int capacity);
		void doScan();
		void doConnect();
		void doPublishUpdate(int updateSlot, const RawMotionSample *updatedSample);
	};
} // namespace wiiviz::Wiimote
