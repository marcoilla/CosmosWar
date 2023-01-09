#include "NetworkManager.h"

int NetworkManager::sockfd;

struct sockaddr_in NetworkManager::server_addr, NetworkManager::client_addr;

bool NetworkManager::ready = false;

bool NetworkManager::transferred = true;

char NetworkManager::server_ip_addr[15];

void NetworkManager::initServerSock() {
    memset(&server_addr, 0, sizeof(struct sockaddr)); // fill serv_addr with '0'
    // set socket family
    server_addr.sin_family = AF_INET;
    // set socket ip
    if (strcmp(server_ip_addr, " ") == 0) {
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        inet_aton(server_ip_addr, &server_addr.sin_addr);
    }
    // set socket port
    server_addr.sin_port = htons(12345);
}

void NetworkManager::initClientSock() {
    memset(&client_addr, 0, sizeof(struct sockaddr)); // fill serv_addr with '0'
    // set socket family
    client_addr.sin_family = AF_INET;
    // set socket ip
    client_addr.sin_addr.s_addr = INADDR_ANY;
    // set socket port
    client_addr.sin_port = 0;
}

void NetworkManager::prepareServer() {
    // create the socket
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("server socket failed");
    }
    // bind the socket
    if (bind(sockfd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind server error");
    }
}

void NetworkManager::prepareClient() {
    // create the socket
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client socket failed");
    }
    // bind the socket
    if (bind(sockfd, (struct sockaddr*) &client_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind client error");
    }
}

void NetworkManager::listenClient(int *data) {
    socklen_t addr_size = sizeof(struct sockaddr);
    recvfrom(sockfd, &*data, sizeof(int), 0, (struct sockaddr*) &client_addr, &addr_size);
    ready = true;
}

void NetworkManager::listenServer(int *data) {
    socklen_t addr_size = sizeof(struct sockaddr);
    recvfrom(sockfd, &*data, sizeof(int), 0, (struct sockaddr*) &server_addr, &addr_size);
    ready = true;
}

void NetworkManager::receiveData(int *data, int size) {
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr);
    printf("Data: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    if (recvfrom(sockfd, data, sizeof(int)*size, 0, (struct sockaddr*)&addr, &addr_size) < 0) {
        perror("recvfrom error");
    }
}

void NetworkManager::sendData(struct sockaddr_in addr, int *data, int size) {
    socklen_t addr_size = sizeof(struct sockaddr);
    if (sendto(sockfd, data, sizeof(int)*size, 0, (struct sockaddr*)&addr, addr_size) < 0) {
        perror("sendto error");
    }
}

void* NetworkManager::serverReceiveWaiting(void *arg) {
    int *data = (int*) arg;
    listenClient(data);
}

void* NetworkManager::clientReceiveWaiting(void *arg) {
    int *data = (int*) arg;
    listenServer(data);
}

void* NetworkManager::receiver(void *arg) {
    int *data = (int*) arg;
    while (true) {
        if (!transferred) {
            NetworkManager::receiveData(data, 4);- .
            rl
            transferred = true;
        }
    }
}

void NetworkManager::close() {
    ready = false;
    ::close(sockfd);
}