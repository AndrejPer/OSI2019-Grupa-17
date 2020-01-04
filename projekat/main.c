#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct event
{
    char name[41];//= {0};
    char desc[501];// = {0}; //description
    char loc[101];// = {0}; //location
    char cat[6];// = {0}; //5-cipher ID of the category
    char date[9] ;//= {0};
    char time[6];// = {0};
} EVENT;

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

void add_event()
{
    EVENT tmp;
    char name[41] = {0};
    char desc[501] = {0}; //description
    char loc[101] = {0}; //location
    int cat[6] = {0}; //5-cipher ID of the category
    char date[9] = {0};
    char time[6] = {0};


    printf("Glad you are adding more events to the database!\n");
    printf("Please enter the following information about the event:\n");

    printf("Name (up to 40 characters): "); scanf(" %s", name);
    printf("Description (up to 500 characters): "); scanf(" %s", desc);
    printf("Location (up to 100 characters): "); scanf(" %s", loc);
    printf("Date (DD/MM/YY): "); scanf(" %s", date);
    printf("Time (HH:MM): "); scanf(" %s", time);

    //add_category_to_event();

    strcpy(tmp.name, name);
    strcpy(tmp.name, name);
    strcpy(tmp.name, name);
    strcpy(tmp.name, name);
    strcpy(tmp.name, name);
}

void delete_event()
{
    FILE *fp1, *fp2;
    char name[41], temp[41], desc[501], loc[101], cat[21], date[9], time[6];
    int i=1;
    if((fp1=fopen("Events.txt", "r")))
    {
        printf("List of all events:\n\n");
        while(fscanf(fp1, "%s %s %s %s %s %s", name, desc, loc, cat, date, time)!=EOF)
            printf("%s %s %s %s %s %s\n", name, desc, loc, loc, date, time);
        rewind(fp1);
        printf("\nPleas name the event you wish to delete!\n");
        scanf("%s", temp);
        while(fscanf(fp1, "%s %s %s %s %s %s", name, desc, loc, cat, date, time)!=EOF)
            if(strcmp(name,temp)==0)
            {
                if((fp2=fopen("Replica.txt", "w")))
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s %s %s %s %s", name, desc, loc, cat, date, time)!=EOF)
                        if(strcmp(name, temp)!=0)
                            fprintf(fp2, "%s %s %s %s %s %s\n", name, desc, loc, cat, date, time);

                    fclose(fp2);
                }

                fclose(fp1);
                remove("Events.txt");
                rename("Replica.txt", "Events.txt");
                if((fp1=fopen("Events.txt", "r")))
                    printf("\nList of events after deletin:\n\n");
                while(fscanf(fp1, "%s %s %s %s %s %s", name, desc, loc, cat, date, time)!=EOF)
                    printf("%s %s %s %s %s %s\n", name, desc, loc, cat, date, time);
            }
            else
            {
                while (i-- == 1)
                    printf("\nThere is no event with that name!\n");

            }
    }
}

void writte_in_file(int n, EVENT *arr, FILE *fp)// pomocna funkcija
{
    int i;
    for(i=0; i<n; i++)
        fprintf(fp,"%s %s %s %s %s %s\n", arr[i].name, arr[i].desc, arr[i].loc, arr[i].cat, arr[i].date, arr[i].time);
}

void sort_newest_date()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s  %s %s", arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
        n++;
    fclose(fin);
    for (h = n / 2; h > 0; h /= 2)
    {
        for (i = h; i < n; i++)
        {
            EVENT temp = arr[i];
            for (j = i; j >= h && strcmp(arr[j - h].date, temp.date) < 0; j -= h)
                arr[j] = arr[j - h];
            arr[j] = temp;
        }
    }
    if ((fout = fopen("Sort_newest_date.txt", "w")))
        writte_in_file(n, arr, fout);
    fclose(fout);
    printf("Napravljen je fajl sa dogadjajima sortiranim po najnovijem datumu!");
}


void sort_by_alphabet()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s  %s %s", arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
        n++;
    fclose(fin);
    for (h = n / 2; h > 0; h /= 2)
    {
        for (i = h; i < n; i++)
        {
            EVENT temp = arr[i];
            for (j = i; j >= h && strcmp(arr[j - h].name, temp.name) > 0; j -= h)
                arr[j] = arr[j - h];
            arr[j] = temp;
        }
    }
    if ((fout = fopen("Sort_by_alphabet.txt", "w")))
        writte_in_file(n, arr, fout);
    fclose(fout);
    printf("Napravljen fajl!");
}

void sort_oldest_date()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s  %s %s", arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
        n++;
    fclose(fin);
    for (h = n / 2; h > 0; h /= 2)
    {
        for (i = h; i < n; i++)
        {
            EVENT temp = arr[i];
            for (j = i; j >= h && strcmp(arr[j - h].date, temp.date) > 0; j -= h)
                arr[j] = arr[j - h];
            arr[j] = temp;
        }
    }
    if ((fout = fopen("Sort_oldest_date.txt", "w")))
        writte_in_file(n, arr, fout);
    fclose(fout);
    printf("Fajl sa dogadjajima sortiranim po najstarijem datumu!");
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
    int a = 0, attempts = 3;

            do
            {
                printf("Username: ");
                scanf(" %s", usern);
                printf("Password: ");
                scanf(" %s", pass);
                a = checking_login(usern, pass, facc);

                if(!a) printf("\nIncorrect username of password.\n");

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
            int p = 0;
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
                    
                else if(admin_choice=='S')
                    {
                        char sort_choice = 0;
                        printf("\nHow would you like to sort?\n");
                        printf("\tSort by newest date [N]\n");
                        printf("\tSort by oldest date [O]\n");
                        printf("\tSort by alphabet [A]\n");
                        scanf("%s", &sort_choice);
                        if(sort_choice=='N')
                            sort_newest_date();
                        if(sort_choice=='A')
                            sort_by_alphabet();
                        if(sort_choice=='O')
                            sort_oldest_date();
                    }

                else if(admin_choice != 'B') printf("Unknown option!");

                }
                while(admin_menu != 'B');
            }
        }


    else if (account == 'G')
    {
        char guest_choice;
        //for registering guest's choice

        do
        {
        printf("What would you like to do?");
        printf("\tView today's events [A]\n");
        printf("\tView past events [B]\n");
        printf("\tView future event [C]\n");
        printf("\tView events by category [D]\n");
        printf("\tPlay the quiz [E]\n");
        printf("\tBack [F]\n");

        scanf(" %c", &guest_choice);

        if(guest_choice == 'A')

        else if(guest_choice == 'B')

        else if(guest_choice == 'C')

        else if(guest_choice == 'D')

        else if(guest_choice != 'E')

        else if(guest_choice != 'F')
        {
            printf("Unknown option!");
        }

        }
        while(guest_choice != 'F');



    }


    }
    while(begin); //we should scrap this

    return 0;
}
