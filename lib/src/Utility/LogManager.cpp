#include <Utility/LogManager.hpp>

#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

namespace Util {
	void LogManager::init() {
		//std::ofstream file("LOGFILE", std::ios_base::out);
	}
	void LogManager::error(const std::string& msg)
	{
		write("ERROR: "+msg);
	}
	
	void LogManager::warning(const std::string& msg)
	{
		write("WARNING: "+msg);
	}
	
	void LogManager::notice(const std::string& msg)
	{
		write("NOTICE: "+msg);
	}
	
	void LogManager::message(const std::string& msg)
	{
		write(msg);
	}
	
	void LogManager::write(const std::string& msg)
	{
		std::ofstream file("LOGFILE", std::ios_base::app);
		time_t currentTime = std::time(nullptr);
		char buffer[64];
		std::strftime(buffer, 24, "%d/%m/%Y - %H:%M:%S: ", std::localtime(&currentTime));
		file << buffer << msg << std::endl;
	}
}