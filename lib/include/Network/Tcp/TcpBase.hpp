#pragma once

#ifndef TCPBASE_HPP
#define TCPBASE_HPP

/*!
 * \file TcpBase.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <string>
#include <vector>
#include <Network/generic.hpp>
#include <iostream>

#include <Network/Utilities/PingService.hpp>
#include <Network/NetAddress.hpp>
#include <Network/Socket.hpp>
 
/*! \class NzTcpBase
	* \brief Abstract base class representing a connected socket using TCP protocol.
	*/
class NzTcpBase : public NzSocket
{
    public:
		/*!
			* \fn TcpBase()
			* \brief  Default class constructor.
			*/
		NzTcpBase();
		NzTcpBase(const NzTcpBase& other) = delete;

		/*!
			* \fn NzTcpBase(const NzNetAddress& address)
			* \brief  Class constructor.
			*/
		NzTcpBase(const NzNetAddress& address, bool fixedBuffer = false);

		/*!
			* \fn NzTcpBase(const NzNetAddress& address, SOCKET sock, bool fixedBuffer = false)
			* \brief  Class constructor.
			*/
		NzTcpBase(const NzNetAddress& address, SOCKET sock, bool fixedBuffer = false);

		/*!if
			* \fn virtual ~NzTcpBase(void)
			* \brief  Destructor.
			*/
		virtual ~NzTcpBase(void);

		/*!
			* \fn virtual NzPacket* read()
			* \brief  Reads a NzPacket* from the socket
			* \return NzPacket* containing the incoming data.
			*/
		virtual NzPacket* Read();

		/*!
			* \fn virtual NzPacket* ReadFrom(NzNetAddress& from)
			* \brief  Reads a NzPacket* from the socket
			* \return NzPacket* containing the incoming data.
			*/
		virtual NzPacket* ReadFrom(NzNetAddress& from);

		/*!
			* \fn virtual void doAsyncRead()
			* \brief  Attempts to read data from the socket.
			* \return Packet* containing the incoming data.
			*/
		virtual void DoAsyncRead();

		/*!
			* \fn virtual NzPacket* write()
			* \brief  Sends a NzPacket* to the remote peer
			* \param packet: data to send.
			*/
		virtual void Write(NzPacket* packet);

		virtual void WriteTo(NzPacket* packet, const NzNetAddress& to);

		/*!
			* \fn virtual void doAsyncWrite()
			* \brief  Sends a Packet* to the remote peer
			* \param packet: data to send.
			*/
		virtual void DoAsyncWrite();

		/*!
			* \fn virtual void start() = 0
			* \brief Starts the socket. Different behavior if the socket is a client or a server.
			*/
		virtual void Start() = 0;

		/*!
			* \fn virtual void Close()
			* \brief Close the socket
			*/
		virtual void Close();

		/*!
			* \fn static std::vector<std::string> getBindableAddresses()
			* \brief List all the addresses available to bind on.
			* \return Vector containing all the IP addresses available.
			*/
		//static std::vector<std::string> getBindableAddresses();


		/*!
			* \fn virtual int32_t getBytesAvailable(uint32_t count = 32)
			* \brief Check if the socket has received data.
			* \return Size of readable data.
			*/
		virtual int32_t GetBytesAvailable(uint32_t count = 32);

    protected:
		int m_currentReadSize; /*< For the asynchroneous read, represents the amount of data to receive */
		int m_currentReadLeft;
		char* m_readBuffer;
		int m_currentWriteSize; /*< For the asynchroneous write, represents the amount of data to send */
		int m_currentWriteLeft;
		char* m_writeBuffer;
    private:
        NzTcpBase& operator= (const NzTcpBase& other) = delete;
};

#endif
