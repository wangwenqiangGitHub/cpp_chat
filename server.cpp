#include "server.h"

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



ChatDataBase* Server:: chatdb = new ChatDataBase;
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
    
    cout << "服务器初始化成功，开始监听客户端" << endl;

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

    cout << buf << sizeof(buf)<<endl;
    // 注册
    Json::Reader reader;        //解析json对象
    Json::FastWriter writer;    //封装json对象
    Json::Value val;
    //{"cmd":"register","user":"小明",“password”:"111111"};
    //#sucess
    //{"cmd":"register_reply","result":"success"};
    if(!reader.parse(buf,val)) //字符串解析成json对象
    {
        cout << "json 解析失败" << endl;
    }

    string cmd = val["cmd"].asString();
    if (cmd == "register") //注册
    {
        //printf("<%s %d>\n",__func__, __LINE__);
        server_register(bev, val);
        //printf("<%s %d>\n",__func__, __LINE__);
    }
    // 登录
}
void Server::event_cb(struct bufferevent* bev, short what, void* ctx)
{ 
}

void Server::server_register(struct bufferevent* bev, Json::Value& val)
{
    //printf("<%s %d>\n",__func__, __LINE__);
    chatdb->my_database_connect("user");
    //printf("<%s %d>\n",__func__, __LINE__);
    if(chatdb->my_database_get_user_exist(val["user"].asString()))//用户存在
    {
        //printf("<%s %d>\n",__func__, __LINE__);
        Json::Value val;
        val["cmd"] = "register_reply";
        val["result"] = "failure";
        //string s = Json::FastWriter().write(val); 
        int res = bufferevent_write(bev,Json::FastWriter().write(val).c_str(),strlen(Json::FastWriter().write(val).c_str()));
        if(res < 0)
            printf("bufferevent_write\n");

    }
    else //用户不存在
    {
        chatdb->my_database_user_password(val["user"].asString(), val["password"].asString());
        Json::Value val;
        val["cmd"] = "register_reply";
        val["result"] = "success";

        string s = Json::FastWriter().write(val);
        if(bufferevent_write(bev, s.c_str(), strlen(s.c_str())) < 0)
        {
            printf("buferevent write\n");
        }
    }

    chatdb->my_database_disconnect();

    
}
