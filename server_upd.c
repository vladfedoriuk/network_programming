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

    struct sockaddr_in serv_addr, client_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //192.168.208.130
    /*if(inet_pton(AF_INET, "192.168.208.130", &serv_addr.sin_addr) == -1){
           perror("inet_pton error\n");
           exit(EXIT_FAILURE);
     }*/
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if(bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))== -1){
       perror("bind failed");
       exit(EXIT_FAILURE);
    }

    int n;
    int len = sizeof(client_addr);
    char message[MAX_LINE] = "\n\0";

    //bzero(buf,sizeof(buf));
    while(1){

    n = recvfrom(sock_fd, (char *)buf, MAX_LINE, 
    MSG_WAITALL, (struct sockaddr*)&client_addr, &len);
    buf[n] = '\0';

    printf("Client: %s\n", buf);
    scanf("%s",message);

    sendto(sock_fd, (char*)message, strlen(message), MSG_CONFIRM, 
      (struct sockaddr*)&client_addr, len);
   }
   close(sock_fd);
   return 0;
}


   


