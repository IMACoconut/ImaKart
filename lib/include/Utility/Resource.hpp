#pragma once

namespace Util {
	
class Resource {
public:
	Resource() : m_refCount(1) {}
	virtual ~Resource() {}

	void drop() {
		if(--m_refCount <= 0)
			delete this;
	}

	void grab() {
		++m_refCount;
	}

private:
	uint32_t m_refCount;
};

}