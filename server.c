#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;

int main(int argc, char* argv[]){
   struct sockaddr_in adres;
   memset(&adres, 0, sizeof(adres));

   adres.sin_family = AF_INET;
   adres.sin_port = htons(atoi(argv[1]));
   adres.sin_addr.s_addr = htonl(INADDR_ANY);

   int sd = socket(AF_INET, SOCK_STREAM, 0);
   bind(sd,(struct sockaddr_in*) &adres, sizeof(adres));
   listen(sd, 10);

   char buf[18] = "Hello, world!\r\n";
   
   while(1){
     int fd = accept(sd, NULL, 0);
     write(fd, buf, sizeof(buf));
     close(fd);
   }
}
