#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file;
    char buffer[100];

    file = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (file == -1) {
        perror("Error creating file");
        return 1;
    }

    write(file, "Hello, UNIX system calls!", 25);
    close(file);

    file = open("example.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    read(file, buffer, 25);
    buffer[25] = '\0';
    printf("File Content: %s\n", buffer);
    close(file);

    if (remove("example.txt") == 0)
        printf("File deleted successfully.\n");
    else
        perror("Error deleting file");

    return 0;
}
