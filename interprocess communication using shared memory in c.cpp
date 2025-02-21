#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SHM_SIZE 1024  
int main() {
    HANDLE hMapFile;
    char *shm_ptr;
    const char *shm_name = "C:\Users\rajes\OneDrive\Pictures\Documents\wxperiment os"; 
    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHM_SIZE, shm_name);
    if (hMapFile == NULL) {
        printf("Could not create file mapping (%d)\n", GetLastError());
        return 1;
    }
    shm_ptr = (char *)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHM_SIZE);
    if (shm_ptr == NULL) {
        printf("Could not map view of file (%d)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }
    strcpy(shm_ptr, "Hello, shared memory in Windows!");
    printf("Data written to shared memory: %s\n", shm_ptr);
    printf("Press Enter to read the shared memory...");
    getchar();
    printf("Data read from shared memory: %s\n", shm_ptr);
    UnmapViewOfFile(shm_ptr);
    CloseHandle(hMapFile);
    return 0;
}
