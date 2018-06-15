//#include "stdafx.h"
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
//
//#include <event2/event-config.h>
//
//#include <WinSock2.h>
//#include <iostream>
//
//#define IP_ADDRESS ("127.0.0.1")
//#define PORT (9951)
//
//int m_isrun = 0;
//
//
//
//
//int tcp_connect_server(const char* server_ip, int port);
//
//
//void cmd_msg_cb(int fd, short events, void* arg);
//void server_msg_cb(struct bufferevent* bev, void* arg);
//void event_cb(struct bufferevent *bev, short event, void *arg);
//
//
//DWORD WINAPI Fun1Proc(LPVOID lpParameter)
//{
//	char t_cin[1024];
//
//	struct bufferevent* bev = (struct bufferevent*)lpParameter;
//
//	while (1) {
//		memset(t_cin, 0, 1024);
//
//		std::cin >> t_cin;
//
//		if (strcmp(t_cin, "exit") == 0) {
//			break;
//		}
//		int len = strlen(t_cin);
//		//把终端的消息发送给服务器端 
//		int ret = bufferevent_write(bev, t_cin, len);
//		if (ret < 0)
//		{
//			perror("read fail ");
//			return 1;
//		}
//	}
//	exit(1);
//
//	return 0;
//}
//
//int main(int argc, char** argv)
//{
//	//加载套接字库  
//	WSADATA wsaData;
//	int iRet = 0;
//	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iRet != 0)
//	{
//		//cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;;
//		return -1;
//	}
//
//	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
//	{
//		WSACleanup();
//		//cout << "WSADATA version is not correct!" << endl;
//		return -1;
//	}
//	//if (argc < 3)
//	//{
//	//	printf("please input 2 parameter\n");
//	//	return -1;
//	//}
//
//
//	//两个参数依次是服务器端的IP地址、端口号  
//	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
//	if (sockfd == -1)
//	{
//		perror("tcp_connect error ");
//		return -1;
//	}
//
//	printf("connect to server successful\n");
//
//
//
//	struct event_base* base = event_base_new();
//
//	struct bufferevent* bev = bufferevent_socket_new(base, sockfd,
//		BEV_OPT_CLOSE_ON_FREE);
//
//	////监听终端输入事件  
//	//struct event* ev_cmd = event_new(base, STDIN_FILENO,
//	//	EV_READ | EV_PERSIST, cmd_msg_cb,
//	//	(void*)bev);
//	//event_add(ev_cmd, NULL);
//	
//	
//	//timeval writetimeout;
//	//timeval readtimeout;	
//	//memset(&writetimeout, 0, sizeof(timeval));
//	//memset(&readtimeout, 0, sizeof(timeval));
//	//readtimeout.tv_sec = 3;
//	////设置超时时间
//	//bufferevent_set_timeouts(bev, &readtimeout, &writetimeout);
//
//	//当socket关闭时会用到回调参数     
//	bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, NULL);
//	bufferevent_enable(bev, EV_READ | EV_PERSIST);
//
//
//	//创建线程发送数据
//	HANDLE hThread1 = CreateThread(NULL, 0, Fun1Proc, (void*)bev, 0, NULL);
//	CloseHandle(hThread1);
//
//
//
//	event_base_dispatch(base);
//
//	WSACleanup();
//	printf("finished \n");
//	return 0;
//}
//
//
//void server_msg_cb(struct bufferevent* bev, void* arg)
//{
//	char msg[1024];
//
//	size_t len = bufferevent_read(bev, msg, sizeof(msg));
//	msg[len] = '\0';
//
//	printf("recv %s from server\n", msg);
//}
//
//
//void event_cb(struct bufferevent *bev, short event, void *arg)
//{
//
//	if (event & BEV_EVENT_EOF)
//		printf("connection closed\n");
//	else if (event & BEV_EVENT_ERROR)
//		printf("some other error\n");
//
//	//这将自动close套接字和free读写缓冲区  
//	bufferevent_free(bev);
//	//struct event *ev = (struct event*)arg;
//	////因为socket已经没有，所以这个event也没有存在的必要了  
//	//event_free(ev);
//}
//
//
//typedef struct sockaddr SA;
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
//	//status = inet_aton(server_ip, &server_addr.sin_addr);
//
//	//if (status == 0) //the server_ip is not valid value  
//	//{
//	//	errno = EINVAL;
//	//	return -1;
//	//}
//
//	sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
//	if (sockfd == -1)
//		return sockfd;
//
//
//	status = ::connect(sockfd, (SA*)&server_addr, sizeof(server_addr));
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