#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <json-c/json.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        exit(1);
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);
    server_addr.sin_addr.s_addr = inet_addr("10.0.16.8");
    int ret = connect(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr));
    if(-1 == ret)
    {
        exit(1);
    }

    struct json_object *obj = json_object_new_object();
    json_object_object_add(obj, "cmd", json_object_new_string("register"));
    json_object_object_add(obj, "user", json_object_new_string("小明"));
    json_object_object_add(obj, "password", json_object_new_string("11111"));
    
    const char* buf = json_object_to_json_string(obj);

    printf("buf:%s\n", buf);
    int nSend = send(sockfd, buf, strlen(buf), 0);
    if( nSend == -1)
        printf("send erro\n");
    char s[128] = {0};
    ret = recv(sockfd, s, sizeof(s), 0);
    printf("接收服务器的回复：%s\n", s);

    close(sockfd);
    return 0;
}
