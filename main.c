// Project: Simple User-Based Text File Manager (with vulnerabilities)
// File: main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_USERS 10
#define MAX_NAME_LEN 100
#define MAX_FILE_NAME 100
#define MAX_TEXT_LEN 1024

// Vulnerable struct with function pointer
typedef struct {
    char username[MAX_NAME_LEN];
    char password[50];
    void (*onLogin)();
} User;

User users[MAX_USERS];
int userCount = 0;
User *currentUser = NULL;

void welcomeMessage() {
    printf("\n[+] Welcome, %s!\n", currentUser->username);
}

void registerUser() {
    if (userCount >= MAX_USERS) return;
    User u;
    printf("Enter username: ");
    gets(u.username); // ❌ Buffer Overflow Vulnerability 1
    printf("Enter password: ");
    scanf("%s", u.password);
    getchar();
    u.onLogin = welcomeMessage;
    users[userCount++] = u;
    printf("User registered.\n");
}

void login() {
    char name[MAX_NAME_LEN];
    char pass[50];
    printf("Enter username: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", pass);
    getchar();

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, name) == 0 && strcmp(users[i].password, pass) == 0) {
            currentUser = &users[i];
            currentUser->onLogin(); // ❌ Function pointer hijack possible (Vuln 6)
            return;
        }
    }
    printf("Invalid credentials!\n");
}

void writeFile() {
    char filename[MAX_FILE_NAME];
    char *text = (char *)malloc(MAX_TEXT_LEN);
    printf("Filename: ");
    scanf("%s", filename);
    getchar();
    printf("Text: ");
    gets(text); // ❌ Buffer Overflow Vulnerability 2

    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "%s", text);
    fclose(fp);
    printf("File saved.\n");
    free(text);
}

void readFile() {
    char filename[MAX_FILE_NAME];
    char buffer[MAX_TEXT_LEN];
    printf("Filename to read: ");
    scanf("%s", filename);
    getchar();

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }
    while (fgets(buffer, MAX_TEXT_LEN, fp)) {
        printf(buffer); // ❌ Format String Vulnerability 3
    }
    fclose(fp);
}

void deleteFile() {
    char filename[MAX_FILE_NAME];
    printf("Enter filename to delete: ");
    scanf("%s", filename);
    getchar();

    char command[150];
    sprintf(command, "rm %s", filename);
    system(command); // ❌ Command Injection Vulnerability 4
    printf("File deleted.\n");
}

void useAfterFreeDemo() {
    char *temp = (char *)malloc(100);
    strcpy(temp, "This is a demo.");
    free(temp);
    printf("Reusing freed memory: %s\n", temp); // ❌ Use After Free Vulnerability 5
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Register\n2. Login\n3. Write File\n4. Read File\n5. Delete File\n6. Use After Free Demo\n7. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: registerUser(); break;
            case 2: login(); break;
            case 3: writeFile(); break;
            case 4: readFile(); break;
            case 5: deleteFile(); break;
            case 6: useAfterFreeDemo(); break;
            case 7: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
