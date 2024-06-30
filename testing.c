 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "homepage.h"

    void takePassword(char pass[20]) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch(); // Use getch() instead of getchar() to read input without echoing it
        if (ch == '\r') { 
            pass[i] = '\0';
            printf("\n");
            break;
        } else if (ch == '\b' || ch == 127) { // Backspace key is pressed
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (ch == '\t' || ch == ' ') { // Tab or Space is pressed
            continue;
        } else {
            pass[i++] = ch;
            printf("*");
        }
    }
}
// Login function
void login() {
    // Nested function to securely take password input and display '*' for each character

    system("cls");
    int attempt = 0, max_attempts = 3;
    char pw[20];
    char correct_password[20] = "143247";
    printf("To gain authorized access to the library management system, please enter the password.\n");

    while (attempt < max_attempts) {
        printf("Enter password: ");
        takePassword(pw);
        printf("\n");
        if (strcmp(pw, correct_password) == 0) {
            printf("Access granted.\n");
            sleep(1);
            homepage();
            return;
        }
        attempt++;
        printf("Wrong password. You have %d attempt(s) left.\n", max_attempts - attempt);
    }

    if (attempt == max_attempts) {
        printf("The system has been locked.\n");
    }
}

int main() {
    login();
    return 0;
}
