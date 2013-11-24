#pragma once

#ifndef PACKETDECODER_HPP
#define PACKETDECODER_HPP

/*!
 * \file PacketDecoder.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */

#include <sstream>
#include <string>

#include <Network/Packet.hpp>

/*! \class NzPacketDecoder
	* \brief Template class used to safety recover type and data from a packet
	*
	*/
class NzPacketDecoder
{
public:

	/*!
		* \fn NzPacketDecoder(Network::NzPacket* packet)
		* \brief  Default class constructor.
		*
		* \param packet : packet to decode
		*/
	/*NzPacketDecoder(NzPacket* packet) : m_stream(packet->stream), m_type(0) {
		m_stream >> m_type; // On récupère l'id
		m_stream.place(NzArchive::nzBuffer_Reader, 0); // On replace le reader à 0
	};
*/
    NzPacketDecoder() = delete;

	static int GetDataType(NzPacket* p)
	{
	    int type;
	    p->stream >> type;
	    p->stream.place(NzArchive::nzBuffer_Reader, 0);
		return type;
	}

	template<typename T>
	static T GetData(NzPacket* p) {
		T pack;
		p->stream >> pack;
		return pack;
	}

private:
	NzPacketDecoder(const NzPacketDecoder& other);
	NzPacketDecoder& operator=(const NzPacketDecoder& other);
	/*NzTextArchive m_stream;
	int m_type;*/
};

#endif
