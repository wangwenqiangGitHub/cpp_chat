#ifndef SERVER_H
#define SERVER_H

#include <event.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <event2/listener.h>

#include "chatInfo.h"
using namespace std;

#define IP "10.0.16.8"
#define PORT 8000
class Server
{
public:
    Server(const char* ip="127.0.0.1", int port = 8000);
    ~Server();

private:
    struct event_base *base;        // 事件集合
    struct evconnlistener *listener;  // 监听事件
    ChatInfo* chatList;                //链表对象，含有两个链表，user group

private:
    static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* addr, int socklen, void *arg);

    static void client_handler(int fd);
    static void read_cb(struct bufferevent * bev, void *ctx);
    static void event_cb(struct bufferevent* bev, short what, void* ctx);
};


#endif
