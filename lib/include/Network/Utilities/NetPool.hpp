#ifndef NETPOOL
#define NETPOOL

/*!
 * \file NetPool.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <string>
#include <vector>
#include <Network/generic.hpp>
#include <iostream>
#include <thread>
#include <atomic>

#include <Network/Socket.hpp>

/*! \class NetPool
	* \brief Pool providing sockets management functions, such as sendToAll() and select().
	* Use this class if you have a large amount of sockets to manage.
	*/
class NzNetPool
{
    public:
		/*!
			* \fn NzNetPool()
			* \brief  Default class constructor.
			*/
		NzNetPool();

		/*!
			* \fn addSocket(NzSocket* socket)
			* \brief  Add socket to the pool.
			* \param socket : socket to add.
			*/
		void AddSocket(NzSocket* socket);

		/*!
			* \fn removeSocket(NzSocket* socket)
			* \brief  Remove socket from the pool.
			* \param socket : socket to delete.
			*/
		void RemoveSocket(NzSocket* socket);

		/*!
			* \fn std::vector<NzSocket*> select()
			* \brief Check every Socket in the pool and returns every readable socket.
			* \return Vector containing readable sockets.
			*/
		std::vector<NzSocket*> Select();

		/*!
			* \fn void sendToAll(NzPacket* packet)
			* \brief Send packet to every socket in the pool
			*/
		void SendToAll(NzPacket* packet);

		/*!
			* \fn void asyncSendToAll(NzPacket* packet)
			* \brief Send packet to every socket in the pool, using asynchroneous method
			*/
		void AsyncSendToAll(NzPacket* packet);

		/*!
			* \fn void run()
			* \brief Starts the async updates' loop
			*/
		void Run();

		/*!
			* \fn void stop()
			* \brief Stops the async updates' loop
			*/
		void Stop();

    protected:
		std::vector<NzSocket*> m_sockets; /*!< Sockets contained into the pool */
		std::atomic<bool> m_isRunning; /*!< State of the pool's run loop */
		std::thread m_thread; /*!< Thread for the run loop */

	private:

		/*!
			* \fn void loop()
			* \brief Does the async updates for each socket on the pool
			*/
		void Loop();
};

#endif
