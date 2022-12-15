
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *ip = "127.0.0.1";
    int port = 3456;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_len;
    int socket_fd;
    int ret;
    char buf[1024];

    //创建TCP协议的套接字
    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_fd < 0) {
        printf("create a udp socket fd failure: [%s]\n", strerror(socket_fd));
        return -1;
    }
    printf("create a udp socket fd[%d] success.\n", socket_fd);

    //创建sockaddr_in，并传入ip和port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //绑定IP和端口
    ret = bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (ret < 0) {
        printf("socket fd[%d] bind on port[%d] for ip address failure. %d\n", socket_fd, port, ret);
        return -1;
    }
    printf("socket fd[%d] bind on port[%d] for ip address success.\n", socket_fd, port);

    //开启循环，接收客户端消息
    while (1) {
        int n = recvfrom(socket_fd, buf, sizeof(buf), 0, (struct sockaddr *) &server_addr, &client_len);
        send(socket_fd, buf, sizeof(buf), n);
    }
}