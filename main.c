#include <stdio.h>
#include <stdlib.h>

int checking_login(char*, char*, FILE*)

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
        
        if(account == 'A')
        {
            int attempts = 3, p = 0;
            //attempts is used to limit number of attempts
            //p is used as a flag for (in)correct login data, 0 for incorrect
            FILE *facc = fopen("Accounts.txt", "r");
            //this is the file where the login data is stored
            char usern[10], pass[10];
            //string for collecting username and password
            
            do
            {
                printf("Username: ");
                scanf(" %s", usern);
                printf("Password: ");
                scanf(" %s", pass);
                p = checking_login(usern, pass, facc);
                
                if(!p) printf("\nIncorrect username of password.\n");
                
                else 
                {   printf("Loging in...\n\n");
                    printf("Welcome %s", username);
                }
                
            }
            while(!p && --attempts >= 0);
            
            if(p)
            {
                //admin menu
            }
        }
        
        
        
    }
    while(begin);

    return 0;
}
