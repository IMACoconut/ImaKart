#pragma once

#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

/*!
 * \file UdpSocket.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 08/07/2012
 */

#include <Network/Udp/UdpBase.hpp>
#include <Network/NetAddress.hpp>

#include <map>

/*! \class NzUdpSocket
	* \brief Class representing a bounded socket to another machine.
	*/
class NzUdpSocket : public NzUdpBase
{
    public:

		/*!
			* \fn NzUdpSocket(const NzNetAddress& address)
			* \brief  Class constructor.
			* \param address: endpoint of the connection.
			*/
		NzUdpSocket(const NzNetAddress& address);

		/*!
			* \fn virtual void Start()
			* \brief Starts socket (do nothing)
			*/
		virtual void Start();

    protected:
        std::map<NzNetAddress, NzPacket*> m_incoming; /*!< */
};

#endif
