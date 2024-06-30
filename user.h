#ifndef usermng_h
#define usermng_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERS_FILE "userdatabase.txt"

typedef struct {
    int id;
    char name[50];
    char email[50];
    int is_active;
    char borrowing_history[500];
    const char *borrowDate;
} User;

User users[MAX_USERS];

void loadUsersFromFile();
void saveUsersToFile();
void registerUser();
void updateUser();
void deleteUser();
void displayUsers();
void recordBorrowingHistory();

#endif
