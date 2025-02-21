#include <stdio.h>
#include <stdlib.h>
#include <io.h>       
#include <fcntl.h>    
#include <sys/stat.h> 
#include <direct.h>  
#include <windows.h> 

int main() {
    int fd;
    struct _stat fileStat;
    struct _finddata_t fileInfo;
    intptr_t handle;
    fd = _open("test.txt", _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened successfully.\n");

    long offset = _lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        perror("_lseek error");
    } else {
        printf("File size (using _lseek): %ld bytes\n", offset);
    }

    if (_stat("test.txt", &fileStat) == -1) {
        perror("_stat error");
    } else {
        printf("File size (using _stat): %ld bytes\n", fileStat.st_size);
        printf("File permissions: %o\n", fileStat.st_mode);
    }

    printf("\nDirectory contents:\n");
    handle = _findfirst("*.*", &fileInfo);
    if (handle == -1) {
        perror("_findfirst error");
    } else {
        do {
            printf("%s\n", fileInfo.name);
        } while (_findnext(handle, &fileInfo) == 0);
        _findclose(handle);
    }

    _close(fd);

    return 0;
}
