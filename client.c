#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char* argv[]){
   int sd = 0;
   struct sockaddr_in serv_addr;

   if(argc!=3){
     printf("\n Usage: %s <ip of server> <port> \n",argv[0]);
     return 1;
   }

   char buf[128];
   memset(&buf, '0', sizeof(buf));
   
   if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
     perror("Couldn't create a socket\n");
     return 2;
   }

   memset(&serv_addr,'0',sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(atoi(argv[2]));
   
  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1){
    perror("inet_pton error\n");
    return 3;
  }
   
  if(connect(sd, (struct sockaddr_in* )&serv_addr, sizeof(serv_addr)) == -1){
    perror("connect error\n");
    return 4;
  }

  int n = 0;
  while(n = read(sd, buf, sizeof(buf))){
    if(write(0, buf, n)!=n){
      perror("write error\n");
    }
  }

 return 0;
}
  
   
   
