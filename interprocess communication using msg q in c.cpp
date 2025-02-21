#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUFFER_SIZE 100

int main() {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa;
    
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE; 
    sa.lpSecurityDescriptor = NULL;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        printf("Pipe creation failed\n");
        return 1;
    }

    printf("Pipe created successfully\n");
    char message[] = "Hello, anonymous pipe!";
    DWORD bytesWritten;
    if (!WriteFile(hWrite, message, strlen(message) + 1, &bytesWritten, NULL)) {
        printf("WriteFile failed\n");
        return 1;
    }
    printf("Producer: Sent data to pipe: %s\n", message);
    CloseHandle(hWrite);
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;
    if (!ReadFile(hRead, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
        printf("ReadFile failed\n");
        return 1;
    }
    printf("Consumer: Received data from pipe: %s\n", buffer);
    CloseHandle(hRead);

    return 0;
}
