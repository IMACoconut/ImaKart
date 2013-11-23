#pragma once

#ifndef UDPBASE_HPP
#define UDPBASE_HPP

/*!
 * \file UdpBase.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <string>
#include <Network/generic.hpp>
#include <iostream>

#include <Network/Socket.hpp>
#include <Network/NetAddress.hpp>

/*! \class NzUdpBase
	* \brief Abstract base class representing a non-connected socket using UDP protocol.
	*/
class NzUdpBase : public NzSocket
{
	public:

		/*!
			* \fn NzUdpBase()
			* \brief  Default class constructor.
			*/
		NzUdpBase();

		/*!
			* \fn NzUdpBase(const NzNetAddress& address)
			* \brief  Class constructor.
			* \param address: endpoint of the connection.
			*/
		NzUdpBase(const NzNetAddress& address);

		/*!
			* \fn virtual ~NzUdpBase(void)
			* \brief  Destructor
			*/
		virtual ~NzUdpBase(void);

		/*!
			* \fn virtual void Close()
			* \brief Close the socket
			*/
		virtual void Close();

		/*!
			* \fn virtual NzPacket* Read()
			* \brief  Reads a NzPacket* from the socket
			* \return NzPacket* containing the incoming data.
			*/
		virtual NzPacket* Read();

		/*!
			* \fn virtual void Write(NzPacket* packet)
			* \brief  Sends a NzPacket* to the remote peer
			* \param packet: data to send.
			*/
		virtual void Write(NzPacket* packet);

        /*!
			* \fn virtual NzPacket* Write()
			* \brief  Sends a NzPacket* to the remote peer contained in m_address
			* \param packet: data to send.
			*/
		virtual void WriteTo(NzPacket* packet, const NzNetAddress& to);

        /*!
			* \fn virtual NzPacket* ReadFrom(NzNetAddress& from);
			* \brief  Read a NzPacket* from a peer. NzNetAddress from will be filled with peer information.
			* \param from: peer who sent the data.
			*/
		virtual NzPacket* ReadFrom(NzNetAddress& from);

		/*!
			* \fn virtual int32_t GetBytesAvailable(uint32_t count = 32);
			* \brief Check if the socket has received data.
			* \return Size of readable data.
			*/
		virtual int32_t GetBytesAvailable(uint32_t count = 32);

	protected:

        virtual void DoAsyncRead() { };
        virtual void DoAsyncWrite() { };
};

#endif
