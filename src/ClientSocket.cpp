#include "TCPClientSocket.h"

#include <WinSock2.h>

#include <iostream>
#include <string>

#define CONNECTING_PORT 1414

namespace TCPClientSocket
{

	SOCKET createSendSocket( short sendPort )
	{
		SOCKET ret; 
		sockaddr_in sockAddr;

		ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if ( ret == INVALID_SOCKET )
		{
			std::cout << "Can't create send socket: error " << WSAGetLastError() << std::endl;
			return ret;
		}

		memset(&sockAddr, 0, sizeof(sockAddr) );

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(sendPort);
		sockAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		if ( connect(ret, (sockaddr*)&sockAddr, sizeof(sockAddr) ) == SOCKET_ERROR )
		{
			std::cout << "Can't connect send socket: error " << WSAGetLastError() << std::endl;
			goto clear;
		}

		return ret;

	clear:

		closesocket(ret);
		return INVALID_SOCKET;
	}

	void example()
	{

		WORD sockVer;
		WSADATA wsaData;
		sockVer = MAKEWORD(1,0);
		memset(&wsaData, 0, sizeof(wsaData) );

		WSAStartup( sockVer, &wsaData );

		auto sndSock = createSendSocket(CONNECTING_PORT);

		if ( sndSock == INVALID_SOCKET )
		{
			WSACleanup();
			return;
		}

		int msgNum = 0;
		std::string sendMsg;
		int sendRet = 0;

		std::cout << "Start send to loopback at " << CONNECTING_PORT << " port" << std::endl;

		do
		{
			Sleep(2000);

			++msgNum;

			sendMsg = std::string( "Send " ) + std::to_string(msgNum) + std::string( " message" );

			sendRet = send(sndSock, sendMsg.c_str(), sendMsg.length(), 0);

		} while( sendRet != SOCKET_ERROR );

		std::cout << "Sending finish with error " << WSAGetLastError() << std::endl;

		shutdown(sndSock, SD_BOTH);
		closesocket( sndSock );
		WSACleanup();
	}

}