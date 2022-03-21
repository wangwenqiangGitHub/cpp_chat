#include "server.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Server::Server(const char* ip, int port)
{
    chatList = new ChatInfo;
    // 创建事件集合
    base = event_base_new();

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    // 创建监听对象
    listener = evconnlistener_new_bind(base, listener_cb, NULL, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 10, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(NULL == listener)
    {
        cout << " evconnlistener_new_bind error" << endl;
        
    }
    // 监听集合
    event_base_dispatch(base); 
}


Server::~Server()
{
    event_base_free(base);
}


void Server::listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* addr, int socklen, void *arg)
{
    cout << "接受客户端" << fd <<endl;

    // 创建工作线程来处理该客户端
    thread client_thread(client_handler, fd);
    //c线程分离
    client_thread.detach();
}

void Server::client_handler(int fd)
{
    //每个线程有单独的base
    struct event_base *base = event_base_new();
    // 创建buffervent对象
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(NULL == bev)
    {
        cout << "buffer event error" << endl;
    }

    // buffer_event设置回调
    bufferevent_setcb(bev, read_cb, NULL, event_cb, NULL);
    bufferevent_enable(bev, EV_READ);

    // 监听客户端是否有数据
    // 监听集合
    event_base_dispatch(base);

    event_base_free(base);
}


void Server::read_cb(struct bufferevent * bev, void *ctx)
{
    //读取
    char buf[1024] = {0};
    int size = bufferevent_read(bev, buf, sizeof(buf));
    if(size < 0)
    {
        cout << "bufferevent_read" << endl;
    }

    cout << buf << endl;
    // 注册
    // 登录
}
void Server::event_cb(struct bufferevent* bev, short what, void* ctx)
{ 
}
