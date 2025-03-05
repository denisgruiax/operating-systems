#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    int file_descriptor = open("file.txt", O_RDONLY);
    char buffer[100] = "";
    read(file_descriptor, &buffer, 100);

    printf("descriptor value: %i\n", file_descriptor);
    printf("content:\n\"%s\"\n", buffer);

    close(file_descriptor);
}