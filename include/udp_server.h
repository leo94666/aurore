#include "sys/socket.h"
#include <netinet/in.h>

typedef struct UDPServer UDPServer;

int init(UDPServer *udpServer);

int sendMsg(UDPServer *udpServer, char *msg,uint32_t len);