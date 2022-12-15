
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *ip="127.0.0.1";

  int port = 3456;
  struct sockaddr_in server_addr;

  struct sockaddr_in client_addr;
  int client_len;
  int socket_fd;
  int ret;
  char buf[1024];

  socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd < 0) {
    printf("create a tcp socket fd failure: [%s]\n", strerror(socket_fd));
    return -1;
  }
  printf("create a tcp socket fd[%d] success.\n", socket_fd);

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_addr.s_addr=inet_addr(ip);

  ret = bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret < 0) {
    printf("socket fd[%d] bind on port[%d] for ip address failure. %d\n",
           socket_fd, port, ret);
    return -1;
  }
  printf("socket fd[%d] bind on port[%d] for ip address success.\n", socket_fd,
         port);

  if (listen(socket_fd, 5) < 0) {
    printf("socket fd[%d] listened on port[%d] for ip address failure. %s\n",
           socket_fd, port, strerror(socket_fd));
    return -1;
  }
  printf("socket fd[%d] listened on port[%d] for ip address success.\n",
         socket_fd, port);



  while (1) {
    client_len = sizeof(&client_addr);
    int client_fd =
        accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
      perror("can't bind local address");
      close(client_fd);
      return -1;
    }

    while (1) {
      memset(buf, 0, sizeof(buf));

      ret = recv(client_fd, buf, sizeof(buf), 0);
      if (ret <= 0) {
        printf("read data from socket[%d] failure: %s\n", client_fd,
               strerror(errno));
        break ;
      }
      printf("read %d data from server client [%d] and echo it back:%s",
             ret, client_fd, buf);

      ret = send(client_fd, buf, ret, 0);
      if (ret < 0) {
        printf("write %d bytes data back to client[%d] failure:%s\n", ret,
               client_fd, strerror(errno));
         close(client_fd);
      }
      printf("write %d bytes data back to client[%d] success:%s\n", ret,
             client_fd, strerror(errno));
    }
  }
}