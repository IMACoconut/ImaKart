#pragma once

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Network/Utilities/PingService.hpp>
#include <Network/generic.hpp>

class NzNetwork
{
	public:
		NzNetwork() = delete;
		~NzNetwork() = delete;

		static bool Initialize();

		static bool IsInitialized();

		static void Uninitialize();

	private:
		static unsigned int s_moduleReferenceCouter;
};

#endif
