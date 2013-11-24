#include <Network/Utilities/NetPool.hpp>

NzNetPool::NzNetPool() : m_sockets(), m_isRunning(false), m_thread()
{
}

void NzNetPool::AddSocket(NzSocket* socket)
{
	if(!socket)
		return;

	std::vector<NzSocket*>::iterator it = m_sockets.begin();
	for(; it != m_sockets.end(); ++it)
	{
		if((*it) == socket)
			return;
	}
	m_sockets.push_back(socket);
}

void NzNetPool::RemoveSocket(NzSocket* socket)
{
	if(!socket)
		return;

	std::vector<NzSocket*>::iterator it = m_sockets.begin();
	for(; it != m_sockets.end(); ++it)
	{
		if((*it) == socket) {
			m_sockets.erase(it);
			return;
		}
	}
}

std::vector<NzSocket*> NzNetPool::Select()
{
	std::vector<NzSocket*> s;
	std::vector<NzSocket*>::iterator it = m_sockets.begin();
	for(; it != m_sockets.end(); ++it)
		if((*it)->GetBytesAvailable() > 0) {
			s.push_back((*it));
		}

	return s;
}

void NzNetPool::SendToAll(NzPacket* packet)
{
	std::vector<NzSocket*>::iterator it = m_sockets.begin();
	for(; it != m_sockets.end(); ++it)
		(*it)->Write(packet);
}

void NzNetPool::AsyncSendToAll(NzPacket* packet)
{
	std::vector<NzSocket*>::iterator it = m_sockets.begin();
	for(; it != m_sockets.end(); ++it)
		(*it)->AsyncWrite(packet);
}

void NzNetPool::Run()
{
	if(m_isRunning)
		return;

	m_isRunning = true;
	m_thread = std::thread(&NzNetPool::Loop, this);
}

void NzNetPool::Stop()
{
	if(!m_isRunning)
		return;

	m_isRunning = false;
	m_thread.join();
}

void NzNetPool::Loop()
{
	while(m_isRunning) {
		std::vector<NzSocket*>::iterator it = m_sockets.begin();
		for(; it != m_sockets.end(); ++it)
			(*it)->UpdateAsync();

		pause(1000);
	}
}
