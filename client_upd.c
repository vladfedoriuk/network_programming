#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include"fcntl.h"

#define MAX_LINE 1024

int main(int argc, char* argv[]){
   char buf[MAX_LINE];
   int sock_fd;

    if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1){
           perror("inet_pton error\n");
           exit(EXIT_FAILURE);
     }
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    int n;
    int len = sizeof(serv_addr);
    char message[MAX_LINE];

    //bzero(buf,sizeof(buf));
    while(1){
      scanf("%s",buf);


      sendto(sock_fd, (char*)buf, strlen(buf), MSG_CONFIRM, 
      (struct sockaddr*)&serv_addr, len);

      n = recvfrom(sock_fd, (char *)message, MAX_LINE, 
           MSG_WAITALL, (struct sockaddr*)&serv_addr, &len);
      message[n] = '\0';

      printf("Server: %s\n",message);
    }
    close(sock_fd);
   return 0;
}

