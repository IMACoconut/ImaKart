#include <Utility/FilePath.hpp>

namespace Util {
	FilePath::FilePath(const std::string& path) {
		unsigned found = path.find_last_of("/\\");
		dir = path.substr(0,found);
		std::string fname = path.substr(found+1);
		found = fname.find_last_of(".");
		if(found < 1)
		{
			file = fname;
			ext = "";
		} else {
			file = fname.substr(0,found);
			ext = fname.substr(found+1);
		}
	}

	std::string FilePath::getExtension() const {
		return ext;
	}
	
	std::string FilePath::getFilename() const {
		return file;
	}

	std::string FilePath::getDirectory() const {
		return dir;
	}

}