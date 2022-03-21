#ifndef CHATINFO_H
#define CHATINFO_H

#include <event.h>
#include <list>
#include <string>
#include "chat_database.h"
#include <iostream>
using namespace std;

// 群最大个数
#define MAXNUM 1024 

struct User
{
    string name;
    struct bufferevent *bev;
};

typedef struct User User;

typedef struct GroupUser
{
    string name;
}GroupUser;

typedef struct Group
{
    string name;
    list<GroupUser> *l;
}Group;



class ChatInfo
{
public:
    ChatInfo();
    ~ChatInfo();
private:
    list<User> *online_user;    //保存所有在线的用户信息
    list<Group> *group_info;    //保存所有群信息
    ChatDataBase* my_database;  //数据库对象
};

#endif
