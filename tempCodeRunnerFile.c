void saveBooksToFile() {
    FILE *file = fopen(BOOKS_FILE, "w");
    if (file) {
        for (int i = 0; i < numBooks; i++) {
            fprintf(file, "BOOK ID: %d\n,TITLE: %s\n,AUTHOR: %s\n,PUBLISHER: %s\n,YEAR PUBLISHED: %d\n,AVAILABILITY: %d\n",
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
    printf("Enter book details:\n");
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
    getchar(); // Consume newline character
    newBook.available = 1;
    newBook.id = numBooks + 1;

    books[numBooks++] = newBook;
    saveBooksToFile();
    printf("Book added successfully.\n");
}