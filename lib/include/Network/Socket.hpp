#pragma once

#ifndef SOCKET_HPP
#define SOCKET_HPP

/*!
 * \file Socket.hpp
 * \author MrFraggy
 * \version 0.1
 * \date 07-08-2012
 *
 */

#include <sstream>
#include <string>
#include <queue>
#include <utility>
#include <functional>
#include <atomic>

#include <Network/Packet.hpp>
#include <Network/NetAddress.hpp>

/*!
* \struct SocketType
* \brief Represents the network protocol used.
*
*/
typedef enum {
    nzSocketType_UDP, /*< Non-connected mode, unsafe */
    nzSocketType_TCP, /*< Connected mode, safest */
    nzSocketType_RAW
} nzSocketType;

/*! \class Socket
	* \brief Abstract base class for both TCP and UDP sockets.
	*
	*/
class NzSocket
{
    public:

		/*!
			* \fn NzSocket(SocketType type, bool fixedBuffer = false)
			* \brief  Default class constructor.
			*
			* \param type: IP protocol to use.
			* \param fixedBuffer: True if the socket uses a fixed buffer, false otherwise.
			*/
        NzSocket(nzSocketType type, bool fixedBuffer = false);

        /*!
			* \fn NzSocket(Sconst NzNetAddress& addr, nzSocketType type, bool fixedBuffer = false)
			* \brief  Default class constructor.
			*
			* \param addr: address/port to use.
			* \param type: IP protocol to use.
			* \param fixedBuffer: True if the socket uses a fixed buffer, false otherwise.
			*/
        NzSocket(const NzNetAddress& addr, nzSocketType type, bool fixedBuffer = false);

        /*!
			* \fn NzSocket(Sconst NzNetAddress& addr, SOCKET sock, ocketType type, bool fixedBuffer = false)
			* \brief  Default class constructor.
			*
			* \param addr: address/port to use.
			* \param sock: socket descriptor for an established connection.
			* \param type: IP protocol to use.
			* \param fixedBuffer: True if the socket uses a fixed buffer, false otherwise.
			*/
        NzSocket(const NzNetAddress& addr, SOCKET sock, nzSocketType type, bool fixedBuffer = false);

		/*!
			* \fn virtual ~NzSocket()
			* \brief  Class destructor.
			*
			*/
		virtual ~NzSocket();

		/*!
			* \fn SocketType getProtocol() const
			* \brief  getter
			*
			* \return Returns the IP protocol used.
			*/
        nzSocketType GetProtocol() const;

		/*!
			* \fn virtual void start() = 0
			* \brief Starts socket (ie call to bind() for a server)
			*
			*/
		virtual void Start() = 0;

		/*!
			* \fn virtual void close() = 0
			* \brief  Closes the socket
			*
			*/
		virtual void Close() = 0;

		/*!
			* \fn virtual Packet* read() = 0
			* \brief  Read packet from the socket
			*
			* \return Packet with a serialized stream containing incoming data.
			*
			*/
        virtual NzPacket* Read() = 0;

        /*!
			* \fn virtual Packet* ReadFrom(NzNetAddress& from) = 0
			* \brief  Read packet from the socket
			*
			* \return Packet with a serialized stream containing incoming data.
			*
			*/
        virtual NzPacket* ReadFrom(NzNetAddress& from) = 0;

		/*!
			* \fn virtual Packet* asyncRead()
			* \brief  Try to read data from the socket and calls func when the packet is fully received
			*
			*/
		virtual void AsyncRead();

		/*!
			* \fn virtual void setAsyncReadCallback(std::function<void (Packet*)> func)
			* \brief  Set func as the callback function called each time a full packet has been read.
			*
			* \param func: function to call.
			*
			*/
		virtual void SetAsyncReadCallback(std::function<void (NzPacket*)> func);

		/*!
			* \fn virtual void write(Packet* packet) = 0
			* \brief  Writes a packet on the socket
			*
			* \param packet: data to send.
			*
			*/
		virtual void Write(NzPacket* packet) = 0;

		/*!
			* \fn virtual void WriteTo(Packet* packet, const NzNetAddress& to) = 0
			* \brief  Writes a packet on the socket
			*
			* \param packet: data to send.
			*
			*/
		virtual void WriteTo(NzPacket* packet, const NzNetAddress& to) = 0;

		/*!
			* \fn virtual void asyncWrite(Packet* packet) = 0
			* \brief  Try to send data on the socket and calls func when the packet is fully sended
			*
			* \param packet: data to send.
			*
			*/
		virtual void AsyncWrite(NzPacket* packet);

		/*!
			* \fn virtual void setAsyncWriteCallback(std::function<void (int)> func)
			* \brief  Set func as the callback function called each time a write has completed.
			*
			* \param func: function to call.
			*
			*/
		virtual void SetAsyncWriteCallback(std::function<void (int)> func);

		/*!
			* \fn virtual void updateAsync()
			* \brief  Try to send data on the socket and calls func when the packet is fully sended
			*
			* \param packet: data to send.
			*
			*/
        virtual void UpdateAsync();

		/*!
			* \fn virtual int32_t GetBytesAvailable(uint32_t count = 32) = 0
			* \brief  Check if the socket have incoming data.
			*
			* \return Count of bytes readable.
			*
			*/
		virtual int32_t GetBytesAvailable(uint32_t count = 32) = 0;


        virtual bool IsBufferFixed() const;

        virtual void SetBufferFixed(bool fixed);

        virtual void SetNonBlocking(bool nonblock);

        virtual bool IsNonBlocking() const;

        virtual void AllowBroadcast(bool allow);

        virtual bool IsBroadcastAllowed() const;

        virtual bool IsTimeout() const;

        virtual int32_t GetPing() const;

        virtual const NzNetAddress& GetBindAddress() const;

    protected:

		/*!
			* \fn virtual void doAsyncRead() = 0
			* \brief  Try to send data on the socket and calls func when the packet is fully sended
			*
			* \param packet: data to send.
			*
			*/
		virtual void DoAsyncRead() = 0;

		/*!
			* \fn virtual void doAsyncWrite() = 0
			* \brief  Try to send data on the socket and calls func when the packet is fully sended
			*
			* \param packet: data to send.
			*
			*/
		virtual void DoAsyncWrite() = 0;

        nzSocketType m_type; /*!< IP protocol used */
		std::queue<NzPacket*> m_asyncWrite; /*!< Waiting queue for packets to be send */
		std::function<void (int)> m_asyncWriteCallback; /*!< Function called each time a packet is sended */
		std::function<void (NzPacket*)> m_asyncReadCallback; /*!< Function called each time a packet is received */

        NzNetAddress m_address; /*!< Represents the endpoint of the socket */
        SOCKET m_sock; /*!< The socket descriptor used to send and receive data */
        
        #ifdef USE_WINDOWS
        	WSAEVENT m_eventsHandler;
        #endif

        bool m_fixedBuffer;
        bool m_nonBlocking;
        bool m_allowBroadcast;
        
        bool m_hasTimedOut;
        uint32_t m_lastKnownPing;
	private:
		NzSocket(const NzSocket& other);
		NzSocket& operator =(const NzSocket& other);
};
#endif // Socket_H
