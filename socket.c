

#include "sys/socket.h"
#include <stdio.h>
#include <string.h>

// https://blog.csdn.net/YanPan12/article/details/121468798

int tcp_server_init(char *ip, int port) {

  //创建临时变量
  struct sockaddr_storage server_addr;


  // 1.创建socket描述符
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0) {
    printf("to create a tcp socket fd failure: [%s]\n", strerror(listen_fd));
    return -1;
  }
  printf("to create a tcp socket fd[%d] success.\n", listen_fd);



}

int main(int argc, char **argv) {}