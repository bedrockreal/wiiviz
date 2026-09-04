#include "Worker.hpp"
#include "Snapshot.hpp"
#include "WiiuseContext.hpp"

#include <cassert>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wiiuse.h>

namespace wiiviz::Wiimote {
	Worker::Worker(SharedSnapshot *sharedSnapshotPtr) {
		m_sharedSnapshotPtr = sharedSnapshotPtr;
	}
	Worker::~Worker() {
		if (m_context != nullptr) {
			delete m_context;
			m_context = nullptr;
		}
	}

	void Worker::doInit(int capacity) {
		m_context = new WiiuseContext(capacity);
		assert(m_context != nullptr);
		m_context->init();

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
		m_context->find(1);

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

		int connectedCount = m_context->connect();

		// done connecting: notify and set connectedCount
		m_sharedSnapshotPtr->modify([connectedCount](Snapshot *s) {
			s->connectInProgress = 0;
			s->connectedCount = connectedCount;
		});
	}

	void Worker::doPublishSnapshot() {
		m_sharedSnapshotPtr->modify([this](Snapshot *s) {
				// printf("doPublishSnapshot: s = %p\n", s);
				s->lastUpdatedTime = glfwGetTime();
				for (int i = 0; i < s->latestSamples.size(); ++i) {
					if (m_context->isWiimoteConnected(i)) {
						auto curWm = m_context->getHandleAt(i);
						// assert(WIIUSE_USING_ACC(curWm));
						// printf("curWm: accel x=%f y=%f z=%f\n", curWm->gforce.x, curWm->gforce.y, curWm->gforce.z);
						memcpy(&s->latestSamples[i].gforce, &curWm->gforce, sizeof(gforce_t));
						s->latestSamples[i].gyro = curWm->exp.mp.angle_rate_gyro;
					}
				}
			});
	}

	bool Worker::run(int capacity) {
		printf("sharedSnapshotPtr = %p\n", m_sharedSnapshotPtr);
		doInit(capacity);
		doScan();
		doConnect();

		while (!m_shutdownRequested.load()) {
			if (m_scanRequested.load()) {
				doScan();
				doConnect();
				m_scanRequested.store(0);
			}

			if (m_context->poll()) {
				doPublishSnapshot();
				auto s = m_sharedSnapshotPtr->read();
				printf("snapshot: accel x=%f y=%f z=%f\n", s.latestSamples[0].gforce.x, s.latestSamples[0].gforce.y, s.latestSamples[0].gforce.z);
			}
		}
		
		// cleanup done when deleting m_context on worker destruction
		return 1;
	}

	void Worker::requestStop() {
		m_shutdownRequested.store(1);
	}
} // namespace wiiviz::Wiimote
