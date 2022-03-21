#ifndef CHAT_DATABASE_H
#define CHAT_DATABASE_H
#include <mysql/mysql.h>
#include <string>
using namespace std;
class ChatDataBase
{
public:
    ChatDataBase();
    ~ChatDataBase();
    void my_database_connect(string databesename);
    int my_database_get_group_name(string* );
    void my_database_get_group_member(string, string&);
private:
    MYSQL* mysql;
};

#endif
