#pragma once

#include <string>

namespace Util {
	class FilePath {
	public:
		FilePath(const std::string& path);

		std::string getExtension() const;
		std::string getFilename() const;
		std::string getDirectory() const;
		std::string getFullPath() const;

	private:
		std::string dir;
		std::string file;
		std::string ext;
	};
}