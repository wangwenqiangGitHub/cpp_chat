#include "chatInfo.h"

ChatInfo::ChatInfo()
{
    online_user = new list<User>;
    group_info = new list<Group>;
    //往groupinfo中添加群信息
    my_database = new ChatDataBase();
    my_database->my_database_connect("chatgroup");
    string group_name[MAXNUM];
    int group_num = my_database->my_database_get_group_name(group_name);
    printf("group_num:%d\n", group_num);
    for(int i = 0; i < group_num; i++)
    {
        printf("group name:%s\n",group_name[i].c_str());
        struct Group g;
        g.name = group_name[i];
        g.l = new list<GroupUser>; // 保存群中所有用户

        string member;
        my_database->my_database_get_group_member(group_name[i],member);
        printf("群成员：%s\n",member.c_str());

        int sp = 0,ep = 0;
        GroupUser u;
        while(1)
        {
            ep = member.find('|', sp);
            if(-1 == ep)
                break;
            u.name = member.substr(sp, ep - sp); 
            g.l->push_back(u);
            sp = ep + 1;
            u.name.clear();
        }
        u.name = member.substr(sp, member.size() - sp);
        g.l->push_back(u);
        group_info->push_back(g);
    }
#if 0 
    for(list<Group>::iterator it = group_info->begin(); it!=group_info->end(); it++)
    {
        cout << "group name: " << it->name << endl;
        for(list<GroupUser>::iterator i = it->l->begin(); i!= it->l->end(); i++)
        {
            cout << "groupe user name: " <<i->name << endl;
        }
    }
#endif
    //打印数据库信息
    for(auto& it : *group_info)
    {
        cout << "group name: " << it.name << endl;
        for(auto& i : *(it.l))
        {
            cout << "groupe user name: " <<i.name << endl;
        }
    }
     my_database->my_database_disconnect();
     cout << "链表初始化成功" << endl;

}

ChatInfo::~ChatInfo()
{
    
}

