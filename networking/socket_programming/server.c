#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void handle_error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[]) {

    if(argc != 3) handle_error("Usage ./server <port> <msg>");
    
    int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listening_socket < 0) handle_error("listening_sock creation");

    struct sockaddr_in sockaddr;
    sockaddr.sin_addr.s_addr = INADDR_ANY; //INADDR_LOOPBACK;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[1]));
    
    if((bind(listening_socket, (struct sockaddr *) &sockaddr, sizeof(sockaddr))) == -1) handle_error("listening_sock bind");
    if((listen(listening_socket, 3)) == -1) handle_error("listening_sock listen");


    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_socket = accept(listening_socket, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_size);
    if(client_socket == -1) handle_error("accept");

    int n_write = write(client_socket, argv[2], strlen(argv[2]));
    if(n_write == -1) handle_error("send");

    close(listening_socket);
    close(client_socket);
    exit(EXIT_SUCCESS);
    return 0;
}
