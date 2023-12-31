#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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

int main(int argc, char const *argv[])
{
    // const char *filename = "./data/helloworld.txt";
    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("file descriptor index: %d\n", fd);
    char buf[1024];
    int nread, total_bytes_read = 0;

    while (1 == 1)
    {
        nread = read(fd, buf, sizeof(buf));
        total_bytes_read += nread;

        if (nread == -1)
        {
            close(fd);
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (nread == 0)
        {
            break;
        }
        printf("%s", get(buf, 0, nread));
    }
    printf("\n");
    printf("Read %d Bytes.\n", total_bytes_read);
    close(fd);
    return EXIT_SUCCESS;
}
