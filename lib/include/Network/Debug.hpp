// Copyright (C) 2012  Andr� Sochard
// This file is part of the "Nazara Engine - Network"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Network/Config.hpp>
#if NAZARA_NETWORK_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
	#include <Core/Debug/MemoryLeakTracker.hpp>

	#define delete NzMemoryManager::NextFree(__FILE__, __LINE__), delete
	#define new new(__FILE__, __LINE__)
#endif
