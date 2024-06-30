#include "user.h"

#define MAX_USERS 100
#define USERS_FILE "userdatabase.txt"

User users[MAX_USERS];
int numUsers = 0;

void loadUsersFromFile() {
    FILE *file = fopen(USERS_FILE, "r");
    if (file) {
        while (fscanf(file, "%d,%[^,],%[^,],%d,%[^\n]\n",
                      &users[numUsers].id, users[numUsers].name,
                      users[numUsers].email, &users[numUsers].is_active,
                      users[numUsers].borrowing_history) == 5) {
            numUsers++;
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading.\n");
    }
}

void saveUsersToFile() {
    FILE *file = fopen(USERS_FILE, "w");
    if (file) {
        for (int i = 0; i < numUsers; i++) {
            fprintf(file, "\nUSER ID: %d\nNAME: %s\nEMAIL: %s\nACTIVE: %d\nBORROWING HISTORY: %s\n",
                    users[i].id, users[i].name, users[i].email,
                    users[i].is_active, users[i].borrowing_history);
        }
        fclose(file);
    } else {
        printf("Error: Could not save users to file.\n");
    }
}

void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Error: Maximum number of users reached.\n");
        return;
    }

    User newUser;

    printf("========== REGISTER USER ==========\n");
    printf("Enter user details: ");

    while(getchar()!='\n');
    printf("\nName: ");
    fgets(newUser.name, 50, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0'; // Remove newline character

    printf("Email: ");
    fgets(newUser.email, 50, stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0';
    
    newUser.is_active = 1;
    newUser.borrowing_history[0] = '\0'; // Initialize borrowing history as empty
    newUser.id = numUsers + 1;

    users[numUsers++] = newUser;
    saveUsersToFile();
    printf("User registered successfully.\n");
}

void updateUser() {
    printf("========== UPDATE USER ==========\n");
    int user_id;
    printf("Enter the ID of the user to update: ");
    scanf("%d", &user_id);
    getchar();

    int found = 0;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            found = 1;
            printf("Enter new details for the user: \n");

            char input[50];
            printf("Name [%s]: ", users[i].name);
            fgets(input, 50, stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = '\0';
                strcpy(users[i].name, input);
            }

            printf("Email [%s]: ", users[i].email);
            fgets(input, 50, stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = '\0';
                strcpy(users[i].email, input);
            }

            printf("Is Active (1 for active, 0 for inactive) [%d]: ", users[i].is_active);
            fgets(input, 10, stdin);
            if (input[0] != '\n') {
                users[i].is_active = atoi(input);
            }

            saveUsersToFile();
            printf("User with ID %d has been updated.\n", user_id);
            break;
        }
    }
    if (!found) {
        printf("User with ID %d not found.\n", user_id);
    }
}

void deleteUser() {
    printf("========== DELETE USER ==========\n");
    int user_id;
    printf("Enter the ID of the user to delete: ");
    scanf("%d", &user_id);
    getchar();

    int found = 0;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            found = 1;
            for (int j = i; j < numUsers - 1; j++) {
                users[j] = users[j + 1];
            }
            numUsers--;
            saveUsersToFile();
            printf("User with ID %d has been deleted.\n", user_id);
            break;
        }
    }
    if (!found) {
        printf("User with ID %d not found.\n", user_id);
    }
}

void recordBorrowingHistory(int user_id, const char *book_title) {
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            strcat(users[i].borrowing_history, book_title);
            strcat(users[i].borrowing_history, "; "); // Assuming semicolon as a separator
            saveUsersToFile();
            break;
        }
    }
}

void displayUsers() {
    if (numUsers == 0) {
        printf("No users in the database.\n");
        return;
    }
    printf("========== USER DATABASE ==========\n");
    for (int i = 0; i < numUsers; i++) {
        printf("ID: %d, Name: %s, Email: %s, Active: %s, Borrowing History: %s\n",
               users[i].id, users[i].name, users[i].email,
               users[i].is_active ? "Yes" : "No", users[i].borrowing_history);
    }
}

int displaymenu(){
    int pick;
        printf("=============== User Management Menu ===============\n");
        printf("\t\t1. Register User\n");
        printf("\t\t2. Update User\n");
        printf("\t\t3. Delete User\n");
        printf("\t\t4. Display Users\n");
        printf("\t\t5. Exit\n");
        printf("===============                      ===============\n");
        printf("Enter your choice: ");
        scanf("%d", &pick);
        return pick;
}

void usermng() {
    loadUsersFromFile();
    int pick;
    do {
        pick = displaymenu(); 
        switch (pick) {
            case 1:
                registerUser();
                break;
            case 2:
                updateUser();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                displayUsers();
                break;
            case 5:
                saveUsersToFile();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (pick != 5);
}
