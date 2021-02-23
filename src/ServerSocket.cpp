#include "TCPServerSocket.h"

//#include <winsock.h>
#include <WinSock2.h>

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

#define LISTENING_PORT 1414

namespace TCPServerSocket
{

	std::atomic<bool> finishWorkers(false);

	void clientWorker( SOCKET sock )
	{
		const int bufLength = 128;
		char inData[bufLength];
		int recvBytes;


		while(true)
		{
			if ( recvBytes = recv(sock, inData, bufLength, 0 ) )
			{
				if ( recvBytes < bufLength - 1 && inData[recvBytes] != '\0' )
					inData[recvBytes] = '\0';
				else 
					inData[bufLength-1] = '\0';

				std::cout << "Client msg: " << inData << std::endl;
			}
			else
			{
				std::cout << "Can't recv data from client: error " << WSAGetLastError() << std::endl;
				break;
			}
		}

		shutdown( sock, SD_BOTH );
		closesocket( sock );
		std::cout << "Client socket colsed" << std::endl;
	}

	SOCKET createListeningSocket( short lstPort )
	{
		SOCKET ret; 
		sockaddr_in sockAddr;

		ret = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if ( ret == INVALID_SOCKET )
		{
			std::cout << "Can't create listening socket: error " << WSAGetLastError() << std::endl;
			return ret;
		}
		
		memset(&sockAddr, 0, sizeof(sockAddr) );

		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(lstPort);
		sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		
		if ( bind( ret, (sockaddr*)&sockAddr, sizeof(sockAddr) ) )
		{
			std::cout << "Can't bind listening socket: error " << WSAGetLastError() << std::endl;
			goto clear;
		}

		if ( listen( ret, SOMAXCONN) )
		{
			std::cout << "Can't start listen listening socket: error " << WSAGetLastError() << std::endl;
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

		auto lstSock = createListeningSocket(LISTENING_PORT);

		if ( lstSock == INVALID_SOCKET )
		{
			WSACleanup();
			return;
		}

		std::cout << "Start listening on " << LISTENING_PORT << " port" << std::endl;

		std::vector<std::thread*> clientsWorkers;

		while(true)
		{
			auto clientSock = accept(lstSock, NULL, 0 );

			if ( clientSock != INVALID_SOCKET )
			{
				std::cout << "Connection established" << std::endl;

				auto worker = new std::thread( clientWorker, clientSock );
				clientsWorkers.push_back(worker);
				continue;
			}
			else
			{
				std::cout << "Error occur during accept operation: erro " << WSAGetLastError() << std::endl;
				std::cout << "Finish listening socket and all active connetions" << std::endl;
				break;
			}
		}

		for( auto clientWorker : clientsWorkers )
		{
			delete clientWorker;
		}

		shutdown(lstSock, SD_BOTH);
		closesocket( lstSock );
		WSACleanup();

		return;
	}

}