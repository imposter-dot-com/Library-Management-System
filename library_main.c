#include"allheaderfiles.h"

int main()
{
    header();
    login();
    
    int choice;
    do{
        choice = homepage();
        switch(choice){
            case 1:
            system("cls");
            bookmng();
            break;
            case 2:
            system("cls");
            usermng();
            break;
            case 3: 
            system("cls");
            borrowreturn();
            break;
            case 4:
            system("cls");
            printf("Exiting. . .");
            header();
            break;
            default:
            printf("Invalid choice. Please choose a number from 1-4");
            break;
        }
    }while (choice!=4);

    return 0;
}

