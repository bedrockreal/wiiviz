#pragma once

namespace wiiviz {
	template <typename T>
	struct Singleton {
	public:
		static T& getInstance() {
			static T instance;
			return instance;
		}

		// Delete copy and move operations to prevent duplication
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	protected:
		Singleton() = default;
		~Singleton() = default;
	};
} // namespace wiiviz
