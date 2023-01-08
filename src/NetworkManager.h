#ifndef ARCADE_GAME_NETWORKMANAGER_H
#define ARCADE_GAME_NETWORKMANAGER_H

#include "include.h"

class NetworkManager {
public:
    static int sockfd;
    static struct sockaddr_in server_addr, client_addr;
    static bool ready;
    static char server_ip_addr[15];
    // methods
    static void initServerSock();
    static void initClientSock();
    static void prepareServer();
    static void prepareClient();
    static void listenClient(int *data);
    static void listenServer(int *data);
    static void receiveData(int *data, int size);
    static void sendData(struct sockaddr_in addr, int *data, int size);
    static void* serverReceiveWaiting(void *arg);
    static void* clientReceiveWaiting(void *arg);
    static void close();
};

#endif //ARCADE_GAME_NETWORKMANAGER_H
