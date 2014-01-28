/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
  int sock, n;
  unsigned int length;
  struct sockaddr_in server, from;
  struct hostent *hp;
  char buffer[256];
   
  if (argc != 3) { printf("Usage: server port\n");
    exit(1);
  }
  sock= socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) error("socket");

  server.sin_family = AF_INET;
  hp = gethostbyname(argv[1]);
  if (hp==0) error("Unknown host");

  bcopy((char *)hp->h_addr, 
	(char *)&server.sin_addr,
	hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  length=sizeof(struct sockaddr_in);
  bzero(buffer,256);
  int number =1;
  int flag=5;
  char temp[]="Write to the socket:";
  while(flag!=0){
    bzero(buffer,256);
    sprintf(buffer,"%d\n",number);
    number++;
    n=sendto(sock,buffer,
	     strlen(buffer),0,(const struct sockaddr *)&server,length);
    if (n < 0) error("Sendto");
    write(1,temp,sizeof(temp));
    write(1, buffer,n);
    bzero(buffer,256);
    //  n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
    //  if (n>0){ 
    //   write(1,"got an ack:",12);
    //    write(1, buffer,n);
    //    flag--;
    //  }
    bzero(buffer,256);
    sleep(2);
  }
  close(sock);
  return 0;
}

void error(const char *msg)
{
  perror(msg);
  exit(0);
}
