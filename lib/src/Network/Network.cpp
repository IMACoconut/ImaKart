#include <Network/Network.hpp>
#include <Utility.hpp>

bool NzNetwork::Initialize()
{
	if (s_moduleReferenceCouter++ != 0)
		return true; // Déjà initialisé


	// Initialisation du module
	#if defined(USE_WINDOWS)
	WSADATA WSAData;
	int err = WSAStartup(MAKEWORD(2,0), &WSAData);
	if(err != 0) {
        Util::LogManager::error("Failed to initialize Network module");
        return false;
	}
	/*if(!NzPingService::Initialize())
    {
        return false;
    }*/
	#endif

	Util::LogManager::notice("Initialized: Network module");

	return true;
}

bool NzNetwork::IsInitialized()
{
	return s_moduleReferenceCouter != 0;
}

void NzNetwork::Uninitialize()
{
    //NzPingService::Uninitialize();

	if (--s_moduleReferenceCouter != 0)
		return; // Encore utilisé

	// Libération du module
    #if defined(USE_WINDOWS)
        WSACleanup();
    #endif

	Util::LogManager::notice("Uninitialized: Network module");
}

unsigned int NzNetwork::s_moduleReferenceCouter = 0;
