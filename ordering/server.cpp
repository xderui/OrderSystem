#include<cstdio>
#include<iostream>
#include<sstream>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main() {
	cout << "欢迎使用接收端，请耐心等待订单的到来\n";
	while (1) {
		WORD socketversion = MAKEWORD(2, 1);
		WSADATA wsa;
		if (WSAStartup(socketversion, &wsa) != 0) {
			cout << "绑定失败！" << endl;
			return -1;
		}
		SOCKET sersocket;
		sersocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sersocket == INVALID_SOCKET) {
			cout << "创建套接字失败！" << endl;
			WSACleanup();
			return -1;
		}
		SOCKADDR_IN seraddr_in;
		seraddr_in.sin_family = AF_INET;
		seraddr_in.sin_port = htons(80);
		seraddr_in.sin_addr.S_un.S_addr = INADDR_ANY;
		if (bind(sersocket, (SOCKADDR*)&seraddr_in, sizeof(seraddr_in)) == SOCKET_ERROR) {
			cout << "绑定套接字失败！" << endl;
			return -1;
		}
		if (listen(sersocket, 2) == SOCKET_ERROR) {
			cout << "建立监听失败！" << endl;
			return -1;
		}
		SOCKET clisocket;
		SOCKADDR_IN cliaddr_in;
		int cliaddrlen = sizeof(cliaddr_in);
		clisocket = accept(sersocket, (SOCKADDR*)&cliaddr_in, &cliaddrlen);
		if (clisocket == INVALID_SOCKET) {
			cout << "接收请求失败！" << endl;
			return -1;
		}
		char recvbuff[BUFSIZ];
		char sendbuff[BUFSIZ];
		while (1) {
			ZeroMemory(recvbuff, BUFSIZ);
			if (recv(clisocket, recvbuff, BUFSIZ, 0) == SOCKET_ERROR) break;
			cout << endl << recvbuff;
			strcpy(sendbuff, " ");
			send(clisocket, sendbuff, strlen(sendbuff), 0);
		}
		closesocket(sersocket);
		closesocket(clisocket);
		WSACleanup();
	}
	return 0;
}