#pragma once
#include <iostream>

namespace Util {
	
class Resource {
public:
	Resource() : m_refCount(1) {}
	virtual ~Resource() {}

	void drop() {
		//std::cout << "dropping " << this << " " << m_refCount-1 << std::endl;
		if(--m_refCount <= 0)
			delete this;
	}

	void grab() {
		//std::cout << "grabbing " << this << " " << m_refCount+1 << std::endl;
		++m_refCount;
	}

	uint32_t getRefCount() const {
		return m_refCount;
	}

private:
	uint32_t m_refCount;
};

}