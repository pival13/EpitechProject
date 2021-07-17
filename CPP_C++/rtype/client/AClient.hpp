#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <cstring>
#include "../server/communication/include/room.hpp"

class AClient
{
	public:
		AClient(std::string ip);
		virtual ~AClient() = 0;

		virtual bool initConnection() = 0;
		virtual bool initUdp() = 0;
		virtual bool receiveTCPHeader() = 0;
		virtual bool receiveUDPHeader() = 0;
		virtual bool receiveTCPMessage() = 0;
		virtual bool sendHeaderToTcpServer(Rtype::Rfc::TcpCode rfcCode) = 0;
		virtual bool setRooms() = 0;
		virtual bool joinRoom(char roomUuid[Rtype::Size::uuidLength]) = 0;
		virtual bool leaveRoom(char roomUuid[Rtype::Size::uuidLength]) = 0;
		virtual bool udpAction(std::vector<unsigned char> data) = 0;
		virtual bool getUpdate() = 0;
		virtual bool doTcpWrite() = 0;
		virtual bool doUdpWrite() = 0;
		virtual void setUdpHeader() = 0;
		virtual bool createRoom(const std::string & name, const short place,
				const short bomb, const short life) = 0;

		std::vector<get_room_t> getRooms() const;
		void setData(void *data, std::size_t length);
		void addData(void *data, std::size_t length);
		void setUdpData(void *data, std::size_t length);
		void addUdpData(void *data, std::size_t length);
		void setTcpHeader(char buffer[sizeof(header_t)]);
		bool isRunning() const;
		bool isUdpRunning() const;
		void stopRunning();
		void stopUdpRunning();
		std::string getRoomUuid() const;
		std::string getIP() const;
		std::vector<unsigned char> getUdpUpdate() const;

	protected:
	    header_t getHeader() const;
		create_room_t makeRoom(const std::string & name, const short place,
				const short bomb, const short life);
		join_room_t makeJoinRoom(char roomuuid[Rtype::Size::uuidLength]);
		leave_room_t makeLeaveRoom(char roomuuid[Rtype::Size::uuidLength]);


	protected:
		header_t _tcpHeader;
		header_udp_output_t _udpHeader;
		std::string _IP;
		char _uuid[Rtype::Size::uuidLength];
		std::string _roomUuid;
		std::vector<get_room_t> _rooms;
		unsigned short _port;
		std::vector<unsigned char> _data;
		std::vector<unsigned char> _udpData;
		std::vector<unsigned char> _update;
		unsigned short _dataSize;
		unsigned short _udpDataSize;
	    bool _running = false;
		bool _udpRunning = false;
};
