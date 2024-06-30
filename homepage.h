#include<stdio.h>
#include<stdlib.h>


int homepage()
{
    int choice;
    system("cls");
    printf("\nWelcome to CADT's library management system.\n");
    printf("===============  Homepage  ===============");
    printf("\n\t1. Book management");
    printf("\n\t2. User management");
    printf("\n\t3. Borrow and return");
    printf("\n\t4. Exit\n");
    printf("===============            ===============\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    return choice;
}

    
