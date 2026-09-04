#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace wiiviz {
	template<typename T>
	// this thread-safe queue is used for
	// 1. wiimote command: main -> wiimote worker
	// 2. wiimote snapshot: wiimote worker -> main
	struct ThreadSafeQueue {
	public:
		void push(const T *cmd) {
			{
				std::scoped_lock lock(m_mutex);
				m_queue.push(*cmd);
			}
			m_cv.notify_one();
		}

		bool tryPop(T *out) {
			std::scoped_lock lock(m_mutex);
			if (m_queue.empty()) {
				return false;
			}
			*out = m_queue.front();
			m_queue.pop();
			return true;
		}

		void wait() {
			std::unique_lock lock(m_mutex);
			m_cv.wait(lock, [&] { return !m_queue.empty(); });
		}

	private:
		std::mutex m_mutex;
		std::condition_variable m_cv;
		std::queue<T> m_queue;
	};
} // namespace wiiviz
