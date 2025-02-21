#include <stdio.h>
#include <string.h>
#define MAX_USERS 5
#define MAX_FILES 5
typedef struct {
    char name[20];
} File;
typedef struct {
    char username[20];
    File files[MAX_FILES];
    int fileCount;
} Directory;
Directory users[MAX_USERS]; 
int userCount = 0;
void createUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    users[userCount].fileCount = 0;
    userCount++;
    printf("User directory created successfully.\n");
}
void createFile() {
    char username[20], filename[20];
    printf("Enter username: ");
    scanf("%s", username);
    int i, j;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (users[i].fileCount >= MAX_FILES) {
                printf("File limit reached for this user!\n");
                return;
            }
            printf("Enter file name: ");
            scanf("%s", filename);
            strcpy(users[i].files[users[i].fileCount].name, filename);
            users[i].fileCount++;
            printf("File created successfully.\n");
            return;
        }
    }
    printf("User not found!\n");
}
void displayFiles() {
    char username[20];
    printf("Enter username: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Files in %s's directory:\n", username);
            for (int j = 0; j < users[i].fileCount; j++) {
                printf("- %s\n", users[i].files[j].name);
            }
            return;
        }
    }
    printf("User not found!\n");
}
void searchFile() {
    char username[20], filename[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter file name to search: ");
    scanf("%s", filename);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = 0; j < users[i].fileCount; j++) {
                if (strcmp(users[i].files[j].name, filename) == 0) {
                    printf("File found in %s's directory.\n", username);
                    return;
                }
            }
            printf("File not found in %s's directory.\n", username);
            return;
        }
    }
    printf("User not found!\n");
}
int main() {
    int choice;
    while (1) {
        printf("\nTwo-Level Directory Structure\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Display Files\n");
        printf("4. Search File\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createUser(); break;
            case 2: createFile(); break;
            case 3: displayFiles(); break;
            case 4: searchFile(); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
