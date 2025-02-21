#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define NAME_SIZE 50

struct File {
    char name[NAME_SIZE];
    int size;
};

struct FileDictionary {
    struct File files[MAX_FILES];
    int count;
};

void addFile(struct FileDictionary *dict, char name[], int size) {
    if (dict->count < MAX_FILES) {
        strcpy(dict->files[dict->count].name, name);
        dict->files[dict->count].size = size;
        dict->count++;
    } else {
        printf("File limit reached!\n");
    }
}

void displayFiles(struct FileDictionary *dict) {
    printf("\nStored Files:\n");
    for (int i = 0; i < dict->count; i++) {
        printf("File: %s, Size: %d KB\n", dict->files[i].name, dict->files[i].size);
    }
}

int main() {
    struct FileDictionary dict = { .count = 0 };

    addFile(&dict, "file1.txt", 120);
    addFile(&dict, "file2.doc", 300);
    addFile(&dict, "image.png", 450);

    displayFiles(&dict);

    return 0;
}
