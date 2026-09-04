#include "Worker.hpp"
#include "Data.hpp"
#include "Snapshot.hpp"
#include "WiimoteManager.hpp"
#include "WiiuseContext.hpp"

#include <cassert>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	Worker::Worker(
			SharedSnapshot *sharedSnapshotPtr,
			MotionSampleQueue **sharedMotionDataStream
	) {
		m_sharedSnapshotPtr = sharedSnapshotPtr;
		m_sharedMotionDataStream = sharedMotionDataStream;
	}
	Worker::~Worker() {
		if (m_wiimoteManager != nullptr) {
			delete m_wiimoteManager;
			m_wiimoteManager = nullptr;
		}
	}

	void Worker::doInit(int capacity) {
		m_wiimoteManager = new WiimoteManager();
		assert(m_wiimoteManager != nullptr);
		assert(m_wiimoteManager->init(capacity));

		// init finish, write to snapshot
		m_sharedSnapshotPtr->modify([](Snapshot *s) {
			s->inited = 1;
		});
	}

	void Worker::doScan() {
		// scanning in progress
		m_sharedSnapshotPtr->modify([](Snapshot *s) {
			s->scanInProgress = 1;
		});

		m_wiimoteManager->scan(1);

		// scannign finished
		m_sharedSnapshotPtr->modify([](Snapshot *s) {
			s->scanInProgress = 0;
		});
	}

	void Worker::doConnect() {
		// connecting in progress
		m_sharedSnapshotPtr->modify([](Snapshot *s) {
			s->connectInProgress = 1;
		});

		int connectedCount = m_wiimoteManager->connect();

		// done connecting: notify and set connectedCount
		m_sharedSnapshotPtr->modify([connectedCount](Snapshot *s) {
			s->connectInProgress = 0;
			s->connectedCount = connectedCount;
		});
	}

	void Worker::doPublishUpdate(int updatedSlot, const RawMotionSample *updatedSample) {
		m_sharedSnapshotPtr->modify([&updatedSlot, &updatedSample](Snapshot *s) {
				s->lastUpdatedTime = updatedSample->time;
				s->latestSamples[updatedSlot] = *updatedSample;
				});
	}

	bool Worker::run(int capacity) {
		doInit(capacity);
		doScan();
		doConnect();

		while (!m_shutdownRequested.load()) {
			if (m_scanRequested.load()) {
				doScan();
				doConnect();
				m_scanRequested.store(0);
			}

			// TODO: publish to queue, if we're recording
			m_wiimoteManager->pollAndUpdate([this](
						int updatedSlot,
						const RawMotionSample *updatedSample
					) {
						// puts("m_wiimoteManager->pollAndUpdate callback");
						this->m_sharedSnapshotPtr->modify([&updatedSlot, &updatedSample](Snapshot *s) {
								s->lastUpdatedTime = updatedSample->time;
								s->latestSamples[updatedSlot] = *updatedSample;
								});
					});
		}
		
		// cleanup done when deleting m_context on worker destruction
		return 1;
	}

	void Worker::requestStop() {
		m_shutdownRequested.store(1);
	}
} // namespace wiiviz::Wiimote
