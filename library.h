#ifndef bookmng_h
#define bookmng_h

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#define MAX_BOOKS 100
#define BOOKS_FILE "bookdatabase.txt"

typedef struct{
    int id;
    char title[50];
    char author[100];
    char publisher[50];
    int year;
    int available;
} Book;

Book books[MAX_BOOKS];


#endif