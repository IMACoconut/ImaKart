// Copyright (C) 2012  Andr� Sochard
// This file is part of the "Nazara Engine - Network"
// For conditions of distribution and use, see copyright notice in Config.hpp

#if NAZARA_NETWORK_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
	#undef delete
	#undef new
#endif
