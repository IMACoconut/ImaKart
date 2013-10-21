#pragma once 
#include <fstream>

namespace util {
	class IFile {
	public:
		IFile(std::ifstream& file) :
			m_file(file)
		{
			if(!m_file.is_open())
				throw -1;
		}

		~IFile() {
			m_file.close();
		}

	private:
		std::ifstream& m_file;
	};

	class OFile {
	public:
		OFile(std::ofstream& file) :
			m_file(file)
		{
			if(!m_file.is_open())
				throw -1;
		}

		~OFile() {
			m_file.close();
		}

	private:
		std::ofstream& m_file;
	};
}