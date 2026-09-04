#pragma once

#include "Data.hpp"

#include <cstring>
#include <ctime>
#include <functional>
#include <mutex>
#include <vector>

namespace wiiviz::Wiimote {
	struct Snapshot {
		bool inited;
		bool scanInProgress;
		bool connectInProgress;
		bool shutdownRequested;
		int connectedCount;

		timespec lastUpdatedTime;
		std::vector<RawMotionSample> latestSamples;
	};

	struct SharedSnapshot {
	public:
		Snapshot read() const {
			std::lock_guard<std::recursive_mutex> lock(mtx);
			return m_snapshot;
		}
		void write(Snapshot newSnapshot) {
			std::lock_guard<std::recursive_mutex> lock(mtx);
			memcpy(&m_snapshot, &newSnapshot, sizeof(Snapshot));
		}
		void reset(const int capacity) {
			std::lock_guard<std::recursive_mutex> lock(mtx);
			m_snapshot.inited = 0;
			m_snapshot.scanInProgress = 0;
			m_snapshot.connectInProgress = 0;
			m_snapshot.shutdownRequested = 0;
			m_snapshot.connectedCount = 0;
			m_snapshot.latestSamples.resize(capacity);
		}

		// modify the snapshot with Snapshot* -> void lambda
		void modify(std::function<void(Snapshot*)> func) {
			std::lock_guard<std::recursive_mutex> lock(mtx);
			func(&m_snapshot);
		}

	private:
		Snapshot m_snapshot;
		mutable std::recursive_mutex mtx;
	};
} // namespace wiiviz::Wiimote
