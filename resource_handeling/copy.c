#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char* argv[]) {
    
    const char *src = argv[1];
    const char *dest = argv[2];

    int srcDescriptor = open(src, O_RDONLY);
    if(srcDescriptor == -1){
        perror("open src");
        exit(EXIT_FAILURE);
    }
    
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int destDescriptor = open(dest, O_CREAT| O_TRUNC | O_WRONLY, permissions);
    if(destDescriptor == -1){
        perror("open dest");
        exit(EXIT_FAILURE);
        close(srcDescriptor);
    }

    char *buf = (char *) malloc(1024 * sizeof(char));
    int n_read, n_write, total_bytes_moved = 0;

    // opened both src and dest
    while (1){
        n_read = read(srcDescriptor, buf, sizeof(buf));
        printf("%s", buf);
        
        if(n_read == -1){
            close(srcDescriptor);
            close(destDescriptor);
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (n_read == 0)
        {
            close(srcDescriptor);
            close(destDescriptor);
            exit(EXIT_SUCCESS);
        }
        

        n_write = write(destDescriptor, buf, n_read);
        if(n_write == -1){
            close(srcDescriptor);
            close(destDescriptor);
            perror("write");
            exit(EXIT_FAILURE);
        }
        total_bytes_moved += n_write;
    }

    printf("Moved %d bytes in total", total_bytes_moved);   
    return 0;
}