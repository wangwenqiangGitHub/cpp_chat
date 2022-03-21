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
            ep = member.find('|');
            if(-1 == ep)
                break;
            u.name = member.substr(sp, ep - sp); 
            g.l->push_back(u);
            sp = ep + 1;
            u.name.clear();
        }
        u.name = member.substr(sp, member.size() - sp);
        group_info->push_back(g);
    }
    
//    for(auto it : group_info)
//    {
//        cout << "group name: " << it->name << endl;
//
//    }


}

ChatInfo::~ChatInfo()
{
    
}

