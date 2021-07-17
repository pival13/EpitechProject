#pragma once

#include <SFML/Network.hpp>

#include "AClient.hpp"
#include "communication/include/player.hpp"
#include "../RFC/rfc.hpp"

class Core: public AClient
{
	public:
		Core(std::string ip = "127.0.0.1");
		~Core();

		bool initConnection();
		bool initUdp();
	    bool receiveTCPHeader();
	    bool receiveUDPHeader();
		bool receiveTCPMessage();
		bool receiveUDPMessage();
		bool sendHeaderToTcpServer(Rtype::Rfc::TcpCode rfcCode);
		bool setRooms();
		bool joinRoom(char roomUuid[Rtype::Size::uuidLength]);
		bool leaveRoom(char roomUuid[Rtype::Size::uuidLength]);
		bool createRoom(const std::string & name, const short place,
				const short bomb, const short life);
		bool doTcpWrite();
		bool doUdpWrite();
		bool udpAction(std::vector<unsigned char> data);
		bool getUpdate();
		void setUdpHeader();

	private:
		sf::IpAddress __recipient;
		sf::TcpSocket __TCPSocket;
		sf::UdpSocket __UDPSocket;
		char __body[Rtype::Size::maxReadSize];
		std::vector<unsigned char> __udpVector;
};
