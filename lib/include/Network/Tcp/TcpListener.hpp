#pragma once

#ifndef TCPLISTENER_HPP
#define TCPLISTENER_HPP

/*!
 * \file TcpListener.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <Network/Tcp/TcpBase.hpp>
#include <Network/Tcp/TcpSocket.hpp>

/*! \class NzTcpListener
	* \brief Class representing a TCP Server socket waiting for incoming connections.
	*/
class NzTcpListener : public NzTcpBase
{
    public:

		/*!
			* \fn NzTcpListener(const NzNetAddress& address)
			* \brief  Class constructor.
			*
			* \param address : address, port, protocol to use.
			*/
        NzTcpListener(const NzNetAddress& address, bool fixedBuffer = false);

		/*!
			* \fn virtual void start()
			* \brief Starts socket (binds on the address/port specified in constructor)
			*/
        virtual void Start();

		/*!
			* \fn virtual NzTcpSocket* waitForClient()
			* \brief Waits for a new client to connect on.
			*
			* \return Returns a NzSocket* containing the new client's information.
			*/
        virtual NzTcpSocket* WaitForClient();

    private:
        uint8_t m_maxClients; /*< Max number of clients in queue */
		nzSocketAddr sin; /*< Connection's information */
		nzSocketProtocol protocol; /*< Protocol used */

		/*!
			* \fn NzTcpListener(const NzTcpListener& other) = delete
			* \brief  Copy constructor disabled.
			*/
		NzTcpListener(const NzTcpListener& other);
};

#endif
