#include <stddef.h>
#include <arpa/inet.h>
#include "udp_server.h"


struct UDPServer {
    const char *dstIp;
    int dstPort;
    struct sockaddr_in serverAddr;
    int fd;
};


int init(UDPServer *udpServer) {
    if (NULL == udpServer || NULL == udpServer->dstIp || 0 == udpServer->dstPort) {
        return -1;
    }

    udpServer->fd= socket(AF_INET,SOCK_DGRAM,0);
    if(udpServer->fd<0){
        return -1;
    }
    udpServer->serverAddr.sin_family=AF_INET;
    udpServer->serverAddr.sin_port= htons(udpServer->dstPort);
    inet_aton(udpServer->dstIp,&udpServer->serverAddr.sin_addr);

    return 0;
}


int sendMsg(UDPServer *udpServer, char *msg,uint32_t len){
    ssize_t num = sendto(udpServer->fd,msg,len,0,(struct sockaddr *)&udpServer->serverAddr, sizeof(udpServer->serverAddr));
    if(num!=len){
        return -1;
    }
    return len;
}