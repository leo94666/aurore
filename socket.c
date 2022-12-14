

#include "sys/socket.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// https://blog.csdn.net/YanPan12/article/details/121468798

int main(int argc, char **argv) {

  // 1.创建临时变量
  char *ip = "127.0.0.1";
  int port = 7890;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int client_len;
  char buf[1024];
  int ret = -1;

  // 2.创建socket描述符
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0) {
    printf("create a tcp socket fd failure: [%s]\n", strerror(listen_fd));
    return -1;
  }
  printf("create a tcp socket fd[%d] success.\n", listen_fd);

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htonl(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ret = bind(listen_fd, &server_addr, sizeof(server_addr));
  if (ret < 0) {
    printf("socket fd[%d] bind on port[%d] for ip address failure.%s\n",
           listen_fd, port, strerror(listen_fd));
    return -1;
  }
  printf("socket fd[%d] bind on port[%d] for ip address success.\n", listen_fd,
         port);
  listen(listen_fd, 13);

  while (1) {
    int client_fd = accept(listen_fd, &client_addr, &client_len);
    if (client_fd < 0) {
      return -1;
    }
    memset(&server_addr, 0, sizeof(buf));
    ret = read(client_fd, buf, sizeof(buf));
    printf("%s", buf);
    if (ret < 0) {
      close(listen_fd);
      continue;
    }
    ret = write(client_fd, buf, ret);
    if (ret < 0) {
      close(listen_fd);
    }
  }
  return 0;
}