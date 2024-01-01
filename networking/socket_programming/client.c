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

char *get(char *buf, int start_index, int n)
{

    if (strlen(buf) == n)
        return buf;

    char *new_buf = (char *)malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
    {
        new_buf[i] = buf[start_index + i];
    }
    return new_buf;
}

int main(int argc, char const *argv[]) {
    if(argc != 2) handle_error("Usage ./client <server:port>");

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0) handle_error("sock creation");

    struct sockaddr_in sockaddr;
    sockaddr.sin_addr.s_addr = INADDR_ANY; //INADDR_LOOPBACK;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[1]));
    socklen_t client_addr_size = sizeof(sockaddr);

    int ok = connect(client_socket, (struct sockaddr *) &sockaddr, client_addr_size);
    if(ok == -1) handle_error("connect");

    char *buf = (char *) malloc(1024 * sizeof(char));
    int n_read, total_bytes_read = 0;
    while (1 == 1) {
        n_read = read(client_socket, buf, 1024);
        total_bytes_read += n_read;

        if (n_read == -1)
        {
            close(client_socket);
            handle_error("recv");
        }

        if (n_read == 0)
        {
            break;
        }
        printf("%s", get(buf, 0, n_read));
    }

    // int n_read = read(client_socket, buf, sizeof(buf));
    // if(n_read == -1) handle_error("recv");

    printf("\nreceived n_bytes %d.\n", total_bytes_read);

    close(client_socket);
    exit(EXIT_SUCCESS);
    return 0;
}