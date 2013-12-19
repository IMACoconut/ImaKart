#include <Game/Network/NetworkConnexion.hpp>
#include <Game/Network/NetworkManager.hpp>

NetworkConnexion::NetworkConnexion(const NzNetAddress& addr) :
	m_address(addr), m_running(true)
{
	NetworkManager::getInstance().addConnexion(this);
}

NetworkConnexion::~NetworkConnexion() {
	m_running = false;
	for(auto& t : m_threads) {
		t.join();
	}
	m_threads.clear();

	while(!m_incoming.empty()) {
		m_incoming.top()->drop();
		m_incoming.pop();
	}
	while(!m_outgoing.empty()) {
		m_outgoing.top()->drop();
		m_outgoing.pop();
	}
}

void NetworkConnexion::start()
{
	m_threads.push_back(std::thread(&NetworkConnexion::sendLoop, this));
	m_threads.push_back(std::thread(&NetworkConnexion::recvLoop, this));
}

void NetworkConnexion::send(NzPacket* p) {
	p->grab();
	std::lock_guard<std::mutex> lock(m_out);
	m_outgoing.push(p);
}

NzPacket* NetworkConnexion::read() {
	std::lock_guard<std::mutex> lock(m_in);
	if(!m_incoming.size())
		return nullptr;

	NzPacket* p = m_incoming.top();
	m_incoming.pop();
	return p;
}

bool NetworkConnexion::hasInboundData() {
	std::lock_guard<std::mutex> lock(m_in);
	return m_incoming.size() != 0;
}

void NetworkConnexion::sendLoop() {
	while(m_running) {
		sendOne();
		pause(100);
	}
}

void NetworkConnexion::recvLoop() {
	while(m_running) {
		recvOne();
		pause(100);
	}
}