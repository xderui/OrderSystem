#ifndef CLIENT_H
#define CLIENT_H

#include<cstdio>
#include<iostream>
#include<stdlib.h>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int client(string sendbuff) {
	WORD SocketVersion = MAKEWORD(2, 1);
	WSADATA wsa;
	if (WSAStartup(SocketVersion, &wsa) != 0)
		cout << "套接字初始化失败！" << endl;
	SOCKET sersocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sersocket == INVALID_SOCKET) {
		cout << "创建套接字失败！" << endl;
		WSACleanup();
		system("pause");
		return -1;
	}
	SOCKADDR_IN seraddr_in;
	seraddr_in.sin_family = AF_INET;
	seraddr_in.sin_port = htons(80);
	InetPton(AF_INET, TEXT("127.0.0.1"), &seraddr_in.sin_addr);
	if (connect(sersocket, (sockaddr*)&seraddr_in, sizeof(seraddr_in)) == SOCKET_ERROR) {
		cout << "连接服务器失败！" << endl;
		closesocket(sersocket);
		WSACleanup();
		system("pause");
		return -1;
	}

	if (send(sersocket, sendbuff.c_str(), sendbuff.length(), 0) == SOCKET_ERROR) {
		cout << "发送失败！" << endl;
		closesocket(sersocket);
		WSACleanup();
		system("pause");
		return -1;
	}
	closesocket(sersocket);
	WSACleanup();
	return 0;
}

#endif // !CLIENT_H