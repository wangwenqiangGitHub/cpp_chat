# libevent

```sh
wget https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz
cd libevent-2
./configure --prefix=/usr
make
sudo make install
```

# mysql
```sh
sudo apt install mysql-server mysql-client libmysqlclient-dev 

sudo apt install mycli
```
- mysql配置
```sql
mysql -uroot -p;
show databases;

#创建两个数据库
create database user;
create database chatgroup;

show databases;

use chatgroup;

#创建群，
create table 学习交流群1 (owner varchar(32), member varchar(2048)) char set utf8;
create table 学习交流群2 (owner varchar(32), member varchar(2048)) char set utf8;
create table 学习交流群3 (owner varchar(32), member varchar(2048)) char set utf8;

show tables;
insert into `学习交流群1` values  ("小张","小王|小李|小张|小孟");
insert into `学习交流群2` values  ("小刘", "小孙|小刘|小孙|小红|小明");
insert into `学习交流群3` values  ("小冯", "小冯|小费|小花");


select * from `学习交流群1`
select * from `学习交流群2`
select * from `学习交流群3`

select member from `学习交流群1`;

#创建user
use user;
#创建表
create table 小明 (password varchar(16), friend varchar(4096));
#查找
show tables like "小明";
#
insert
# 删除
drop table 小明；


```

# jsoncpp
```sh
sudo apt install libjsoncpp-dev

```
# json-c
```sh
sudo apt install libjson-c-dev
```

# 服务器注册
1. 注册， 客户端发送
```json
{"cmd":"register","user":"小明",“password”:"111111"};
#sucess
{"cmd":"register_reply","result":"success"};
#sucess
{"cmd":"register_reply","result":"failure"};

```


