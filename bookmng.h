#include"library.h"
int numBooks = 0;

void loadBooksFromFile() {
    FILE *file = fopen(BOOKS_FILE, "r");
    if (file) {
        while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d,%d\n",
                     &books[numBooks].id, books[numBooks].title,
                     books[numBooks].author, books[numBooks].publisher,
                     &books[numBooks].year, &books[numBooks].available) == 6) {
            numBooks++;
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading.\n");
    }
}

void saveBooksToFile() {
    FILE *file = fopen(BOOKS_FILE, "w");
    if (file) {
        for (int i = 0; i < numBooks; i++) {
            fprintf(file, "\nBOOK ID: %d\nTITLE: %s\nAUTHOR: %s\nPUBLISHER: %s\nPUBLISHED YEAR: %d\nAVAILABILITY: %d\n",
                    books[i].id, books[i].title, books[i].author,
                    books[i].publisher, books[i].year, books[i].available);
        }
        fclose(file);
    } else {
        printf("Error: Could not save books to file.\n");
    }
}

void addBook() {
    if (numBooks >= MAX_BOOKS) {
        printf("Error: Maximum number of books reached.\n");
        return;
    }

    Book newBook;

    printf("\n========== ADD BOOK ==========\n");
    printf("Enter book details:\n");

    while(getchar() != '\n'); //clear input buffer before using fgets
    printf("Title: ");
    fgets(newBook.title, 100, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline character

    printf("Author: ");
    fgets(newBook.author, 50, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Publisher: ");
    fgets(newBook.publisher, 50, stdin);
    newBook.publisher[strcspn(newBook.publisher, "\n")] = '\0';

    printf("Year: ");
    scanf("%d", &newBook.year);
    while (getchar()!='\n'); // Consume newline character
    newBook.available = 1;
    newBook.id = numBooks + 1;

    books[numBooks++] = newBook;
    saveBooksToFile();
    printf("Book added successfully.\n");
}

void displayBooks() {
    if (numBooks == 0) {
        printf("No books in the database.\n");
        return;
    }

    printf("Book Database:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, Title: %s, Author: %s, Publisher: %s, Year: %d, Available: %s\n",
               books[i].id, books[i].title, books[i].author, books[i].publisher,
               books[i].year, books[i].available ? "Yes" : "No");
    }
}

void searchBooks() {
    char searchTerm[100];
    
    while (getchar()!='\n');
    printf("Enter search term: ");
    fgets(searchTerm, 100, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0'; // Remove newline character

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (strstr(books[i].title, searchTerm) || strstr(books[i].author, searchTerm) ||
            strstr(books[i].publisher, searchTerm)) {
            printf("ID: %d, Title: %s, Author: %s, Publisher: %s, Year: %d, Available: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].publisher,
                   books[i].year, books[i].available ? "Yes" : "No");
            found++;
        }
    }

    if (found == 0) {
        printf("No books found matching the search term.\n");
    }
}

void deleteBook() {
    int book_id;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", &book_id);
    getchar();

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == book_id) {
            found = 1;
            for (int j = i; j < numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            numBooks--;
            saveBooksToFile();
            printf("Book with ID %d has been deleted.\n", book_id);
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", book_id);
    }
}

void updateBook() {
    int book_id;
    printf("Enter the ID of the book to update: ");
    scanf("%d", &book_id);
    getchar();

    int found = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == book_id) {
            found = 1;
            printf("Enter new details for the book (leave blank to keep current value):\n");

            char input[100];
            printf("Title [%s]: ", books[i].title);
            fgets(input, 100, stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = '\0';
                strcpy(books[i].title, input);
            }

            printf("Author [%s]: ", books[i].author);
            fgets(input, 50, stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = '\0';
                strcpy(books[i].author, input);
            }

            printf("Publisher [%s]: ", books[i].publisher);
            fgets(input, 50, stdin);
            if (input[0] != '\n') {
                input[strcspn(input, "\n")] = '\0';
                strcpy(books[i].publisher, input);
            }

            printf("Year [%d]: ", books[i].year);
            fgets(input, 10, stdin);
            if (input[0] != '\n') {
                books[i].year = atoi(input);
            }

            printf("Availability (1 for available, 0 for not available) [%d]: ", books[i].available);
            fgets(input, 10, stdin);
            if (input[0] != '\n') {
                books[i].available = atoi(input);
            }

            saveBooksToFile();
            printf("Book with ID %d has been updated.\n", book_id);
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", book_id);
    }
}

int displayMenu(){
    int choice;
        printf("\n========== BOOK MANAGEMENT MENU ==========\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Books\n");
        printf("4. Delete Book\n");
        printf("5. Update Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        return choice;
}

void bookmng() {
    loadBooksFromFile();
    int choice;
    do {
        choice = displayMenu();
        switch (choice) {
            case 1:
                system("cls");
                addBook();
                break;
            case 2:
                system("cls");
                displayBooks();
                break;
            case 3:
                system("cls");
                searchBooks();
                break;
            case 4:
                system("cls");
                deleteBook();
                break;
            case 5:
                system("cls");
                updateBook();
                break;
            case 6:
                saveBooksToFile();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return;
}