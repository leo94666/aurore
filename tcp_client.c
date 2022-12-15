

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char ** argv){
  char *ip="127.0.0.1";
  int port=3456;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int socket_fd;

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd < 0) {
    printf("create a tcp socket fd failure: [%s]\n", strerror(socket_fd));
    return -1;
  }
  printf("create a tcp socket fd[%d] success.\n", socket_fd);


  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  if(connect(socket_fd,(struct sockaddr *) &server_addr, sizeof(server_addr))<0){
    printf("connect to server failure : [%s]\n", strerror(socket_fd));
    return -1;
  }
  printf("connect to server success\n");
  while (1){

  }

}