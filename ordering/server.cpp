#include<cstdio>
#include<iostream>
#include<sstream>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main() {
	cout << "��ӭʹ�ý��նˣ������ĵȴ������ĵ���\n";
	while (1) {
		WORD socketversion = MAKEWORD(2, 1);
		WSADATA wsa;
		if (WSAStartup(socketversion, &wsa) != 0) {
			cout << "��ʧ�ܣ�" << endl;
			return -1;
		}
		SOCKET sersocket;
		sersocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sersocket == INVALID_SOCKET) {
			cout << "�����׽���ʧ�ܣ�" << endl;
			WSACleanup();
			return -1;
		}
		SOCKADDR_IN seraddr_in;
		seraddr_in.sin_family = AF_INET;
		seraddr_in.sin_port = htons(80);
		seraddr_in.sin_addr.S_un.S_addr = INADDR_ANY;
		if (bind(sersocket, (SOCKADDR*)&seraddr_in, sizeof(seraddr_in)) == SOCKET_ERROR) {
			cout << "���׽���ʧ�ܣ�" << endl;
			return -1;
		}
		if (listen(sersocket, 2) == SOCKET_ERROR) {
			cout << "��������ʧ�ܣ�" << endl;
			return -1;
		}
		SOCKET clisocket;
		SOCKADDR_IN cliaddr_in;
		int cliaddrlen = sizeof(cliaddr_in);
		clisocket = accept(sersocket, (SOCKADDR*)&cliaddr_in, &cliaddrlen);
		if (clisocket == INVALID_SOCKET) {
			cout << "��������ʧ�ܣ�" << endl;
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