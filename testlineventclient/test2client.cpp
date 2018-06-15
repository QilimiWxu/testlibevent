//#include "stdafx.h"
//#include <iostream>
//#include <string.h>
//#include <errno.h>
//#include <stdio.h>
//#include <signal.h>
//
//#include "event2/bufferevent.h"
//#include "event2/buffer.h"
//#include "event2/listener.h"
//#include "event2/util.h"
//#include "event2/event.h"
//
//#include <assert.h>
////#include <event2/event-config.h>
//
//#include <WinSock2.h>
//
//#define IP_ADDRESS ("127.0.0.1")
//#define PORT (9951)
//
//int tcp_connect_server(const char* server_ip, int port)
//{
//	int sockfd = 0, status = 0, save_errno;
//	struct sockaddr_in server_addr;
//
//	memset(&server_addr, 0, sizeof(server_addr));
//
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.s_addr = inet_addr(server_ip);
//	server_addr.sin_port = htons(port);
//
//	sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
//	if (sockfd == -1)
//		return sockfd;
//
//
//	status = ::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
//
//	if (status == -1)
//	{
//		save_errno = errno;
//		closesocket(sockfd);
//		errno = save_errno; //the close may be error  
//		return -1;
//	}
//
//	evutil_make_socket_nonblocking(sockfd);
//
//	return sockfd;
//}
//
//void socket_read_cb(int fd, short events, void *arg)
//{
//	char msg[1024];
//
//	//为了简单起见，不考虑读一半数据的情况  
//	int len = recv(fd, msg, sizeof(msg) - 1, 0);
//	if (len <= 0)
//	{
//		perror("read fail ");
//		exit(1);
//	}
//
//	msg[len] = '\0';
//
//	printf("recv %s from server\n", msg);
//}
//
//DWORD WINAPI Fun1Proc(LPVOID lpParameter)
//{
//	char t_cin[1024];
//	int sockfd = (int)lpParameter;
//	int ret = 0;
//
//	while (1) {
//		memset(t_cin, 0, 1024);
//
//		std::cin >> t_cin;
//
//		if (strcmp(t_cin, "exit") == 0) {
//			break;
//		}
//		//发送数据
//		ret = send(sockfd, t_cin, strlen(t_cin), 0);
//
//		if (ret == -1) {
//			return 1;
//		}
//
//		//cmd_msg_cb(sockfd, 0, t_cin);
//	}
//	exit(1);
//
//	return 0;
//}
//
//int main(int argc, char** argv) {
//	//加载套接字库  
//	WSADATA wsaData;
//	int iRet = 0;
//	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iRet != 0)
//	{
//		//cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;;
//		return -1;
//	}
//	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
//	{
//		WSACleanup();
//		//cout << "WSADATA version is not correct!" << endl;
//		return -1;
//	}
//	//两个参数依次是服务器端的IP地址、端口号  
//	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
//	if (sockfd == -1)
//	{
//		perror("tcp_connect error ");
//		return -1;
//	}
//	struct event_base *base = event_base_new();
//	assert(base != NULL);
//
//	//创建并绑定一个event
//	struct event *listen_event;
//	//参数：event_base, 监听的fd，事件类型及属性，绑定的回调函数，给回调函数的参数
//	listen_event = event_new(base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void*)base);
//	//参数：event，超时时间(struct timeval *类型的，NULL表示无超时设置)
//	event_add(listen_event, NULL);
//
//
//	HANDLE h = CreateThread(NULL, 0, Fun1Proc, (void*)sockfd, 0, NULL);
//	CloseHandle(h);
//
//	//启动事件循环
//	event_base_dispatch(base);
//
//
//	WSACleanup();
//	return 1;
//}
//
//
