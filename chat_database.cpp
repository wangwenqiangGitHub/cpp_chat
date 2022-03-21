#include "chat_database.h"
#include <stdio.h>

ChatDataBase::ChatDataBase()
{
}

ChatDataBase::~ChatDataBase()
{
    mysql_close(mysql);
}

void ChatDataBase::my_database_connect(string databasename)
{
    //创建mysql对象并初始化，返回对象的地址
    mysql = mysql_init(NULL);
    //

    mysql = mysql_real_connect(mysql, "localhost", "root", "root", databasename.c_str(),0 , NULL, 0);

    if(NULL == mysql)
    {
        printf("mysql_real_connect erro\n");
    }
}


int ChatDataBase::my_database_get_group_name(string* s)
{
    if(mysql_query(mysql, "set names utf8;"))
        printf("mysql_query\n");
    if(mysql_query(mysql, "show tables;") != 0)
        printf("my_database_get_group_name mysql_query erro\n");
    MYSQL_RES* res =  mysql_store_result(mysql);
    if(NULL == res)
        printf("mysql_stroe_result\n");
    
    int count = 0;
    MYSQL_ROW row;
    while(row =  mysql_fetch_row(res))
    {
        s[count] += row[0];
        count++;
    }
    return count;
}


bool ChatDataBase::my_database_get_user_exist(string user)
{
    //printf("<%s %d>\n",__func__, __LINE__);
    if(mysql_query(mysql, "set names utf8;"))
        printf("mysql_query\n");
    char sql[1024] = {0};
    sprintf(sql, "show tables like '%s';", user.c_str());
    if(mysql_query(mysql, sql) != 0)
        printf("mysql_query error %s %d\n",__func__,__LINE__);
    MYSQL_RES* res = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    if(NULL == row)
    {
        return false;    
    }
    else
    {
        return true;
    }

}


void ChatDataBase::my_database_user_password(string name, string password)
{
   char sql[128] = {0};
   sprintf(sql,"create table %s (password varchar(16), friend varchar(4096));",name.c_str());
   if(mysql_query(mysql, sql) != 0)
   {
       printf("creat table error\n");
   }
   
   memset(sql, 0 , sizeof(sql));
   sprintf(sql, "insert into `%s` (password) values ('%s');", name.c_str(), password.c_str());
   if(mysql_query(mysql, sql) != 0)
   {
       printf("creat table error\n");
   }
}

void ChatDataBase::my_database_get_group_member(string name, string &s)
{
    char sql[1024] = {0};
    sprintf(sql, "select member from %s;", name.c_str());
    if(mysql_query(mysql, sql) != 0)
        printf("mysql_query error %s %d\n",__func__,__LINE__);
    MYSQL_RES* res = mysql_store_result(mysql);
    if(NULL == res)
    {
        printf("res = mysql_store_result(mysql) erro\n");
    }

    MYSQL_ROW row = mysql_fetch_row(res);

    s += row[0];
}

void ChatDataBase::my_database_disconnect()
{
    mysql_close(mysql);
}
