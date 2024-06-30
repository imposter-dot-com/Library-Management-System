#define FINE_PER_DAY 1.0

double calculateFine(const char *borrowDate, const char *returnDate);
void displayFine(int user_id, int book_id);

void borrowBook() {
    int user_id, book_id;

    printf("==========  BORROW BOOK ==========\n");
    printf("Enter User ID: ");
    scanf("%d", &user_id);
    printf("Enter Book ID: ");
    scanf("%d", &book_id);

    int userIndex = -1, bookIndex = -1;
    
    // Find the user
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            userIndex = i;
            break;
        }
    }

    // Find the book
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == book_id) {
            bookIndex = i;
            break;
        }
    }

    // Check if user and book were found
    if (userIndex == -1) {
        printf("Error: User not found.\n");
        return;
    }

    if (bookIndex == -1) {
        printf("Error: Book not found.\n");
        return;
    }

    // Check if the book is available
    if (!books[bookIndex].available) {
        printf("Error: Book is not available.\n");
        return;
    }

    // Mark the book as borrowed
    books[bookIndex].available = 0;


    // Capture current date as borrowed date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char borrowDate[11];
    sprintf(borrowDate, "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    
    // Update user's borrowing history
    char borrowed_book[100];
    snprintf(borrowed_book, 100, "Borrowed Book ID: %d, Title: %s, Borrowed Date: %s\n", books[bookIndex].id, books[bookIndex].title, borrowDate);
    strncat(users[userIndex].borrowing_history, borrowed_book, 500 - strlen(users[userIndex].borrowing_history) - 1);
    
    books[bookIndex].available = 0;
    
    saveBooksToFile();
    saveUsersToFile();
    printf("Book borrowed successfully.\n");
    printf("Borrowed Book ID: %d\nTitle: %s\nBorrowed Date: %s\n", books[bookIndex].id, books[bookIndex].title, borrowDate);
}

void returnBook() {
    int user_id, book_id;

    printf("========== RETURN BOOK ==========\n");

    printf("Enter User ID: ");
    scanf("%d", &user_id);
    printf("Enter Book ID: ");
    scanf("%d", &book_id);

    int userIndex = -1, bookIndex = -1;

    // Find the user
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            userIndex = i;
            break;
        }
    }

    // Find the book
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == book_id) {
            bookIndex = i;
            break;
        }
    }

    // Check if user and book were found
    if (userIndex == -1) {
        printf("Error: User not found.\n");
        return;
    }

    if (bookIndex == -1) {
        printf("Error: Book not found.\n");
        return;
    }

    // Check if the book is already available
    if (books[bookIndex].available) {
        printf("Error: Book is already available.\n");
        return;

    }

    char returnDate[11];
    printf("Enter return date (YYYY-MM-DD): ");
    scanf("%s", returnDate);


   // Update user's borrowing history
    char returned_book[100];
    snprintf(returned_book, 100, "Returned Book ID: %d, Title: %s, Return Date: %s\n", books[bookIndex].id, books[bookIndex].title, returnDate);
    strncat(users[userIndex].borrowing_history, returned_book, 500 - strlen(users[userIndex].borrowing_history) - 1);

    // Calculate and display fine
    displayFine(user_id, book_id);
    
    books[bookIndex].available = 1;
    
    saveBooksToFile();
    saveUsersToFile();
    printf("Book returned successfully.\n");
    printf("Returned Book ID: %d\nTitle: %s\nReturned Date: %s\n", books[bookIndex].id, books[bookIndex].title, returnDate);

}

double calculateFine(const char *borrowDate, const char *returnDate) {

    struct tm borrow_tm = {0}, return_tm = {0};

    // Parse borrow date
    sscanf(borrowDate, "%4d-%2d-%2d", &borrow_tm.tm_year, &borrow_tm.tm_mon, &borrow_tm.tm_mday);
    borrow_tm.tm_year -= 1900;
    borrow_tm.tm_mon -= 1;

    // Parse return date
    sscanf(returnDate, "%4d-%2d-%2d", &return_tm.tm_year, &return_tm.tm_mon, &return_tm.tm_mday);
    return_tm.tm_year -= 1900;
    return_tm.tm_mon -= 1;

    // Convert struct tm to time_t
    time_t borrow_time = mktime(&borrow_tm);
    time_t return_time = mktime(&return_tm);

    // Calculate difference in days
    double difference = difftime(return_time, borrow_time) / (60 * 60 * 24);

    // Calculate fine
    return (difference > 14) ? (difference - 14) * FINE_PER_DAY : 0.0;
}

void displayFine(int user_id, int book_id) {
    int userIndex = -1, bookIndex = -1;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].id == user_id) {
            userIndex = i;
            break;
        }
    }

    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == book_id) {
            bookIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Error: User not found.\n");
        return;
    }

    if (bookIndex == -1) {
        printf("Error: Book not found.\n");
        return;
    }

    // Capture current date as return date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char returnDate[11];

    books[bookIndex].available = 1;

    // Calculate fine based on borrowed date and return date
    double fine = calculateFine(users[userIndex].borrowDate, returnDate);
    if (fine > 0) {
        printf("Late return. Fine: $%.2f\n", fine);
    } else {
        printf("Book returned on time. No fine.\n");
    }
} 

int menu(){
    int choice;
    printf("========== MENU ==========\n");
    printf("\t1. Borrow\n");
    printf("\t2. Return\n");
    printf("\t3. Exit\n");
    printf("==========      ==========\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void borrowreturn (){
    int choice;
    do {
        choice = menu();
        switch(choice){
            case 1:
                system("cls");
                borrowBook();
                break;
            case 2:
                system("cls");
                returnBook();
                break;
            case 3:
                system("cls");
                printf("Exiting. . .");
                homepage();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }while (choice!=3);
}