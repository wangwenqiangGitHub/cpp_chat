#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

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

    char buf[32] = "hello server";
    int nSend = send(sockfd, buf, sizeof(buf), 0);

//    while(1)
//    {
//        printf("please input send data"\n);
//        
//        if(!nSend || nSend == SOCKET_ERROR)
//            break;
//    }
//
    close(sockfd);
    return 0;
}
