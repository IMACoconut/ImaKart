#pragma once

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

/*!
 * \file TcpSocket.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <Network/Tcp/TcpBase.hpp>

/*! \class NzTcpSocket
	* \brief Class representing a connected socket using TCP protocol.
	*/
class NzTcpSocket : public NzTcpBase
{
    public:

		/*!
			* \fn NzTcpSocket(const NzNetAddress& address, SOCKET sock)
			* \brief  Class constructor.
			*
			* \param address : peer information.
			* \param sock : socket descriptor
			*/
		NzTcpSocket(const NzNetAddress& address, SOCKET sock, bool fixedBuffer = false);

		/*!
			* \fn NzTcpSocket(const NzNetAddress& remoteAddress, int timeout = 5)
			* \brief  Class constructor.
			*
			* \param remoteAddress : remote host to connect to.
			* \param timeout : delay before aborting the connection attempts.
			*/
        NzTcpSocket(const NzNetAddress& remoteAddress, bool fixedBuffer = false, int32_t timeout = 5, bool nonBlocking = true);

		/*!
			* \fn virtual void start() = 0
			* \brief Starts socket (attempts to connect to the remote host)
			*/
        virtual void Start();

		/*!
			* \fn virtual bool isConnected()
			* \brief Check if the socket is connected to a remote host.
			*
			* \return true if connected, false otherwise
			*/
		virtual bool IsConnected();

	protected:
		bool m_connected; /*!< Represents the state of the connection */
		int32_t m_timeout; /*!< Time (in sec) before stopping the connection attempts */

	private:
		/*!
			* \fn NzTcpSocket(const NzTcpSocket& other) = delete
			* \brief  Copy constructor disabled.
			*/
		NzTcpSocket(const NzTcpSocket& other);
};

#endif
