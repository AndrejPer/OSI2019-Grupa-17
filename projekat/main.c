#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checking_login(char username[], char password[], FILE *fp)
{
    char temp_username[20],  temp_password[20];

        while (fscanf(fp, "%s %s",temp_username, temp_password )!=EOF)
        {

            if(strcmp(username,temp_username)==0 && strcmp(password, temp_password)==0)
                return 1;
        }
    return 0;

}
void delete_event(int* admin_menu)
{
    FILE *fp1, *fp2;
    char name[20], temp[20], opis[20], lok[20], kategorija[20], datum[20], vrijeme[20];

    if(fp1=fopen("Events.txt", "r"))
    {
        while(fscanf(fp1, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
            printf("%s %s %s %s %s %s\n", name, opis, lok, kategorija, datum, vrijeme);
        rewind(fp1);
            printf("Name the event you wish to delete ");
            scanf("%s", temp);
            while(fscanf(fp1, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
                if(strcmp(name,temp)==0)
                {
                    if(fp2=fopen("Replica.txt", "w"))
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
                        if(strcmp(name, temp)!=0)
                        fprintf(fp2, "%s %s %s %s %s %s\n", name, opis, lok, kategorija, datum, vrijeme);

                fclose(fp2);
                }
                }
        fclose(fp1);
        }
        remove("Events.txt");
        rename("Replica.txt", "Events.txt");
        if(fp2=fopen("Events.txt", "r"))
        while(fscanf(fp2, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
            printf("%s %s %s %s %s %s\n", name, opis, lok, kategorija, datum, vrijeme);

}

void view_events(int* admin_menu)
{
    FILE *fp;
    char name[20], opis[20], lok[20], kategorija[20], datum[20], vrijeme[20];
    if(fp=fopen("Events.txt", "r"))
    while(fscanf(fp, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
    printf("%s %s %s %s %s %s\n", name, opis, lok, kategorija, datum, vrijeme);
}

int admin_login()
{
    FILE *facc = fopen("Accounts.txt", "r");
    //this is the file where the login data is stored
    char usern[30], pass[30];
    //string for collecting username and password
    int a = 0;

            do
            {
                printf("Username: ");
                scanf(" %s", usern);
                printf("Password: ");
                scanf(" %s", pass);
                a = checking_login(usern, pass, facc);

                if(!p) printf("\nIncorrect username of password.\n");

                else
                {   printf("Loging in...\n\n");
                    printf("Welcome %s", usern);//username
                }

            }
            while(!a && --attempts >= 0);

    return a;
}


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

            p = admin_login();

            if(p)
            {
                char admin_choice = 0;
                //for registering admin's choice
                int admin_menu = 0;
                //for facilitating the return to the admin menu in combo with do while loop

                do
                {

                printf("What would you like to do?");
                printf("\tAdd event [A]\n");
                printf("\tChange event details [C]\n");
                printf("\tDelete event [D]\n");
                printf("\tView events [V]\n");
                printf("\tSort events [S]\n");
                printf("\tDelete event category [E]\n");
                printf("\tAdd event category [T]\n");
                printf("\tBack [B]\n");

                scanf(" %c", &admin_choice);

                if (admin_choice == 'A')

                else if(admin_choice == 'D')
                    delete_event(&admin_menu);
                else if(admin_choice == 'V')
                    view_events(&admin_menu);

                }
                while(admin_menu != 0);
            }
        }



    }
    while(begin); //we should scrap this

    return 0;
}
