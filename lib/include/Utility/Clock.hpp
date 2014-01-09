#pragma once

#include <chrono>

namespace Util {
class Clock {
	public:
		Clock()
		{
			Restart();
		}

		uint32_t GetMilliseconds() const {
			auto elapsed = std::chrono::system_clock::now();
			if(!paused)
				return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed-begin).count();
			else
				return std::chrono::duration_cast<std::chrono::milliseconds>(pause-begin).count();

		}
		uint32_t GetSeconds() const {
			auto elapsed = std::chrono::system_clock::now();
			if(!paused)
				return std::chrono::duration_cast<std::chrono::seconds>(elapsed-begin).count();
			else
				return std::chrono::duration_cast<std::chrono::seconds>(pause-begin).count();
		}
		uint32_t GetMinutes() const {
			auto elapsed = std::chrono::system_clock::now();
			if(!paused)
				return std::chrono::duration_cast<std::chrono::minutes>(elapsed-begin).count();
			else
				return std::chrono::duration_cast<std::chrono::minutes>(pause-begin).count();
		}

		void Pause() {
			if(!paused)
				pause = std::chrono::system_clock::now();
			paused = true;
		}

		void Resume() {
			if(paused) {
				auto elapsed = std::chrono::system_clock::now();
				begin += (elapsed-pause);
			}
			paused = false;
		}

		void Restart() {
			begin = std::chrono::system_clock::now();
			paused = false;
		}

	private:
		std::chrono::time_point<std::chrono::system_clock> begin, pause;
		bool paused;
};
}