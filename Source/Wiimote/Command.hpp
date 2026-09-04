#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

#include <Common/ThreadSafeQueue.hpp>

namespace wiiviz::Wiimote {
	enum class CommandType {
		StartScan,
		StopScan,
		SetRumble,
		SetLedMask,
		Shutdown
	};

	struct Command {
		CommandType type;
		int slot = -1;
		bool boolValue = false;
		int intValue = 0;
	};

	/*
	class CommandQueue {
	public:
		void push(const Command *cmd) {
			{
				std::scoped_lock lock(m_mutex);
				m_queue.push(*cmd);
			}
			m_cv.notify_one();
		}

		bool tryPop(Command *out) {
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
		std::queue<Command> m_queue;
	};
	*/
	typedef wiiviz::ThreadSafeQueue<Command> CommandQueue;
} // namespace wiiviz::Wiimote
