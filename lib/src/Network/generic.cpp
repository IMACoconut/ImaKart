#include <Network/generic.hpp>


#if defined(USE_WINDOWS)
	void pause(uint32_t msec) {
		Sleep(1000);
	}

#elif defined(USE_LINUX)
	void pause(uint32_t msec) {
		usleep(msec);
	}
#else
	void pause(uint32_t msec) {}
#endif