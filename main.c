#include <stdio.h>
#include <stdlib.h>

int main()
{
    char begin = 0, account = 0;

    printf("Welcome! Let's explore!\n");

    do
    {
        printf("\nHow are you logging in?\n");
        printf("Admin [A] or Guest [G]: \n");
        scanf(" %c", &account);
        //printf("%c", account);
    }
    while(begin);

    return 0;
}
