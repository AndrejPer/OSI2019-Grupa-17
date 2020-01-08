#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ENTER 13
#define TAB 9
#define BKSP 8

typedef struct event
{
    char name[41];//= {0};
    char desc[501];// = {0}; //description
    char loc[101];// = {0}; //location
    char cat[16];// = {0}; //5-cipher ID of the category
    char date[11] ;//= {0};
    char time[6];// = {0};
    char id[6];//5-character id of the event
} EVENT;

typedef struct
{
    char question[51];
    char ans1[31];
    char ans2[31];
    char ans3[31];
    char true_answ[2];
} QUIZ;

int admin_login();
int checking_login(char*, char*, FILE*);
void add_event();
void delete_event();
void write_in_file(int, EVENT*, FILE*);
void sort_newest_date();
void sort_by_alphabet();
void sort_oldest_date();
void delete_category();
void add_category();
void list_categories();
void change_event_details();
void view_events();
void guest_view_events(int);
void view_future_events();
void view_past_events();
void view_todays_events();
void events_by_category();
void quiz();
void view_event_details();
void comment( char*);
void list_categories(FILE *);

int main()
{
    char account = 0;

    printf("Welcome! Let's explore!\n");

    do
    {
        printf("\nHow are you logging in? (type 0 to exit)\n");
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
                printf("Successful login!\n");

                char admin_choice = 'B';
                //for registering admin's choice

                do
                {
                    printf("\nWhat would you like to do?\n");
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
                        add_event();

                    else if(admin_choice == 'C')
                        change_event_details();

                    else if(admin_choice == 'D')
                        delete_event();

                    else if(admin_choice == 'V')
                        view_events();

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

                    else if(admin_choice == 'E')
                        delete_category();

                    else if(admin_choice == 'T')
                        add_category();

                    else if(admin_choice != 'B')
                    {
                        printf("Unknown option!");
                        //getchar();
                    }

                }
                while(admin_choice != 'B');
            }

            else
            {
                printf("\nFailed login!\n");
            }

        }


        else if (account == 'G')
        {
            char guest_choice = 'F';
            //for registering guest's choice

            do
            {
                printf("What would you like to do?\n");
                printf("\tView today's events [A]\n");
                printf("\tView past events [B]\n");
                printf("\tView future event [C]\n");
                printf("\tView events by category [D]\n");
                printf("\tPlay the quiz [E]\n");
                printf("\tBack [F]\n");

                scanf(" %c", &guest_choice);

                if(guest_choice == 'A')
                    view_todays_events();
                    //guest_view_events(1);

                else if(guest_choice == 'B')
                    view_past_events()
                    //guest_view_events(0);

                else if(guest_choice == 'C')
                    view_future_events();
                    //guest_view_events(2);

                else if(guest_choice == 'D')
                    events_by_category();

                else if(guest_choice == 'E')
                    quiz();

                else if(guest_choice != 'F')
                {
                    printf("Unknown option!\n");
                    //getchar();
                }

            }
            while(guest_choice != 'F');
        }

        else if (account != '0' && account != 'A');//for some weird reason
        {
            printf("Unknown option!\n");
            getchar(); //might be needed
        }
    }
    while(account != '0');

    return 0;
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

        if(!a)
            printf("\nIncorrect user-name or password.\n");

        else
        {
            printf("Logging in...\n\n");
            printf("Welcome %s", usern);//username
        }

    }
    while(!a && --attempts >= 0);
    fclose(facc);
    return a;
}

int checking_login(char username[], char password[], FILE *fp)
{
    char temp_username[20],  temp_password[20];
    while (fscanf(fp, "%s %s",temp_username, temp_password )!=EOF)
    {
        if(strcmp(username,temp_username) == 0 && strcmp(password, temp_password) == 0)
            return 1;
    }
    return 0;
}
/*
void view_events()
{
    FILE *fp;
    char name[20], opis[20], lok[20], kategorija[20], datum[20], vrijeme[20];
    if((fp = fopen("Events.txt", "r")))
    while(fscanf(fp, "%s %s %s %s %s %s", name, opis, lok, kategorija, datum, vrijeme)!=EOF)
    printf("%s %s %s %s %s %s\n", name, opis, lok, kategorija, datum, vrijeme);
}
*/
void view_events()
{
    FILE *fp;
    EVENT pom;
    int n,i;
    if((fp=fopen("Events.txt", "r"))!=0)
    {
        while(fscanf(fp, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
        {
            n=strlen(pom.name);
            printf("EVENT NAME: ");
            for(i=0; i<n; i++)
                if(pom.name[i]=='/')
                    printf(" ");
                else printf("%c",pom.name[i]);
            printf(" ");

            printf("\n");

             n=strlen(pom.desc);
             printf("EVENT DETAILS: ");
            for(i=0; i<n; i++)
                if(pom.desc[i]=='/')
                    printf(" ");
                else
                    printf("%c",pom.desc[i]);
            printf(" ");

            printf("\n");

             n=strlen(pom.loc);
             printf("EVENT LOCATION: ");
            for(i=0; i<n; i++)
                if(pom.loc[i]=='/')
                    printf(" ");
                else printf("%c",pom.loc[i]);
            printf(" ");printf("\n");
            printf("EVENT CATEGORY: "); print_category(pom.cat);   printf("\n");
            printf("EVENT DATE: "); printf("%s ",pom.date);printf("\n");
            printf("EVENT TIME: "); printf("%s",pom.time);printf("\n");
            printf("\n");
        }
        fclose(fp);
    }
}

void print_category(char *catID)
{
    FILE* fcat = 0;
    char cat_name[15] = {0}, cat_id[6] = {0};
    if((fcat = fopen("Categories.txt", "r"))!= 0)
        while(fscanf(fcat, "%s %s", cat_name, cat_id) != EOF)
            if(strcmp(catID, cat_id) == 0) printf("%s ", cat_name);
    fclose(fcat);
}

void write(EVENT ev)
{
    int i,n;
     printf("ID:\n%s\n",ev.id);
                printf("Name:\n");
                n=strlen(ev.name);
                for(i=0; i<n; i++)
                    if(ev.name[i]=='/')
                        printf(" ");
                    else printf("%c",ev.name[i]);
                printf("\n");
                printf("Description:\n");
                n=strlen(ev.desc);
                for(i=0; i<n; i++)
                    if(ev.desc[i]=='/')
                        printf(" ");
                    else
                        printf("%c",ev.desc[i]);
                printf("\n");
                printf("Category:\n%s \n",ev.cat);
                // printf("%s \n",pom.cat);
                printf("Location:\n");
                n=strlen(ev.loc);
                for(i=0; i<n; i++)
                    if(ev.loc[i]=='/')
                        printf(" ");
                    else printf("%c",ev.loc[i]);
                printf("\n");
                printf("Time and Date:\n");
                printf("%s ",ev.date);
                printf("%s",ev.time);
                printf("\n\n");
}
/*
void add_event()
{
    EVENT tmp;
    char name[41] = {0};
    char desc[501] = {0}; //description
    char loc[101] = {0}; //location
    int cat[6] = {0}; //5-cipher ID of the category
    char date[9] = {0};
    char time[6] = {0};


    printf("\nGlad you are adding more events to the database!\n");
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
*/
/*
void add_event()
{
    EVENT *temp,ev;
    FILE *fp1,*fp2,*fp3;
    char categ[8],id[6],cat2[8];
    printf("Glad you are adding more events to the database!\n");
    printf("Please enter the following information about the event:\n");
    temp=malloc(sizeof(EVENT));
    printf("Name (up to 40 characters) and instead ' ' write '/'  ");
    scanf(" %s", temp->name);
    printf("Description (up to 500 characters) and instead ' ' write '/' ");
    scanf(" %s", temp->desc);
    printf("Location (up to 100 characters) and instead ' ' write '/'  ");
    scanf(" %s", temp->loc);

    printf("List of categories: \n");
    if((fp3=fopen("Categories.txt","r"))!=0)
    {
        int a=0;
        while( fscanf(fp3,"%s %s",categ,id)!=EOF)
            printf("%s %s\n", categ,id);

        while(a==0)
        {
            rewind(fp3);

            printf("Category(up to 6 characters):\n");
            scanf("%s",cat2);
            while((fscanf(fp3,"%s %s",categ,id)!=EOF) )
            {

                if(strcmp(categ,cat2)==0)
                {
                    strcpy(temp->cat,cat2);
                    a++;
                }
            }
        }
        fclose(fp3);
    }

    printf("Date (DD/MM/YY): ");
    scanf(" %s", temp->date);
    printf("Time (HH:MM): ");
    scanf(" %s", temp->time);
    if((fp1=fopen("Events.txt","r"))!=0)
    {

        if((fp2=fopen("new.txt","w"))!=0)
        {
            rewind(fp1);
            while(fscanf(fp1, "%s %s %s %s %s %s", ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
                fprintf(fp2,"%s %s %s %s %s %s\n",ev.name,ev.desc,ev.loc,ev.cat,ev.date,ev.time);
            fprintf(fp2,"%s %s %s %s %s %s\n",temp->name,temp->desc,temp->loc,temp->cat,temp->date,temp->time);
            fclose(fp2);
        }
        fclose(fp1);
    }
    remove("Events.txt");
    rename("new.txt","Events.txt");
    printf("\nList of events after adding:\n\n");
    view_events();
    free(temp);
}
*/

void add_event()
{
    EVENT *temp,ev;
    FILE *fp1,*fp2,*fp3;
    char categ[28],cat2[28];
    printf("Glad you are adding more events to the database!\n");
    printf("Please enter the following information about the event:\n");
    temp=malloc(sizeof(EVENT));
    if((fp1=fopen("Events.txt","r"))!=0)
    {
        int b;
        char pom[6];
        do
        {
            b=0;
            printf("ID (up to 40 characters)\n");
            scanf("%s",pom);
            rewind(fp1);
            while(fscanf(fp1, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
            {
                if(strcmp(pom,ev.id)==0)
                {
                    printf("Try again!\n");

                    b--;
                }
                else strcpy(temp->id,pom);
            }
        }
        while(b<0);
        fclose(fp1);
    }
    printf("Name (up to 40 characters) and instead ' ' write '/'  ");
    scanf(" %s", temp->name);
    printf("Description (up to 500 characters) and instead ' ' write '/' ");
    scanf(" %s", temp->desc);
    printf("Location (up to 100 characters) and instead ' ' write '/'  ");
    scanf(" %s", temp->loc);

    printf("List of categories: \n");
    if((fp3=fopen("Categories.txt","r"))!=0)
    {
        int a=0;
        while( fscanf(fp3,"%s",categ)!=EOF)
            printf("%s\n", categ);

        while(a==0)
        {
            rewind(fp3);

            printf("Category(up to 6 characters):\n");
            scanf("%s",cat2);
            while((fscanf(fp3,"%s",categ)!=EOF) )
            {

                if(strcmp(categ,cat2)==0)
                {
                    strcpy(temp->cat,cat2);
                    a++;
                }
            }
        }
        fclose(fp3);
    }

    printf("Date (DD/MM/YY): ");
    scanf(" %s", temp->date);
    printf("Time (HH:MM): ");
    scanf(" %s", temp->time);
    if((fp1=fopen("Events.txt","r"))!=0)
    {

        if((fp2=fopen("new.txt","w"))!=0)
        {
            rewind(fp1);
            while(fscanf(fp1, " %s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
                fprintf(fp2,"%s %s %s %s %s %s %s\n",ev.id, ev.name,ev.desc,ev.loc,ev.cat,ev.date,ev.time);
            fprintf(fp2,"%s %s %s %s %s %s %s\n",temp->id,temp->name,temp->desc,temp->loc,temp->cat,temp->date,temp->time);
            fclose(fp2);
        }
        fclose(fp1);
    }
    remove("Events.txt");
    rename("new.txt","Events.txt");
    printf("\nList of events after adding:\n\n");
    view_events();
    free(temp);
}
/*
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
}*/

void delete_event()
{
    FILE *fp1, *fp2;
    EVENT pom;
    char temp[20];
    int j=0, m=0;
    if((fp1=fopen("Events.txt", "r"))!=0)
    {
        printf("List of all events:\n\n");
        while(fscanf(fp1, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
        {
            write(pom);
            m++;
        }
        rewind(fp1);
        printf("\nPleas ID od the event you wish to delete ( instead ' ' write '/'!)\n");
        scanf("%s", temp);
        while(fscanf(fp1, "%s %s %s %s %s %s %s", pom.id,pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
            if(strcmp(pom.id,temp)==0)
            {
                if((fp2=fopen("Replica.txt", "w"))!=0)
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
                        if(strcmp(pom.id, temp)!=0)
                            fprintf(fp2, "%s %s %s %s %s %s %s\n",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time);

                    fclose(fp2);
                }

                fclose(fp1);
                remove("Events.txt");

                rename("Replica.txt", "Events.txt");

                printf("\nList of events after deletin:\n\n");
                view_events();
            }
            else
            {
                j++;
                if(j==m)
                    printf("\nThere is no event with that name!\n");
            }
    }
}
/*
void change_event_details()
{
    FILE *fp1, *fp2;
    EVENT pom,*temp;
    temp=malloc(sizeof(EVENT));
    char change_event[41],admin_choice;
    int i=0, m=0;
    if((fp1=fopen("Events.txt", "r"))!=0)
    {
        printf("List of all events:\n\n");
        while(fscanf(fp1, "%s %s %s %s %s %s", pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
        {
            printf("%s ",pom.name);
            int n=strlen(pom.desc),i;
            for(i=0; i<n; i++)
                if(pom.desc[i]=='/')
                    printf(" ");
                else
                    printf("%c",pom.desc[i]);
            printf(" ");
            printf("%s ",pom.loc);
            printf("%s ",pom.cat);
            printf("%s ",pom.date);
            printf("%s\n",pom.time);
            m++;
        }
        rewind(fp1);
        printf("\nPleas name the event you wish to change!\n");
        scanf("%s", change_event);
        while(fscanf(fp1, "%s %s %s %s %s %s", pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
            if(strcmp(pom.name,change_event)==0)
            {
                if((fp2=fopen("Change.txt", "w"))!=0)
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s %s %s %s %s", pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
                        if(strcmp(pom.name, change_event)!=0)
                            fprintf(fp2, "%s %s %s %s %s %s\n", pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time);
                        else
                        {
                            strcpy(temp->name,pom.name);
                            strcpy(temp->desc,pom.desc);
                            strcpy(temp->loc,pom.loc);
                            strcpy(temp->cat,pom.cat);
                            strcpy(temp->date,pom.date);
                            strcpy(temp->time,pom.time);

                            do
                            {
                                printf("\nWhat would you like to change?\n");
                                printf("\tName [N]\n");
                                printf("\tDescription[O]\n");
                                printf("\tLocation [L]\n");
                                printf("\tCategory [C]\n");
                                printf("\tDate [D]\n");
                                printf("\tTime[T]\n");
                                printf("\tBack [B]\n");
                                scanf(" %c", &admin_choice);
                                if(admin_choice=='N')
                                {
                                    printf("Name (up to 40 characters): ");
                                    scanf(" %s", temp->name);
                                }
                                if(admin_choice=='O')
                                {
                                    printf("Description (up to 500 characters) and instead ' ' write '/' ");
                                    scanf(" %s", temp->desc);
                                }
                                if(admin_choice=='L')
                                {
                                    printf("Location (up to 100 characters): ");
                                    scanf(" %s", temp->loc);
                                }
                                if(admin_choice=='C')
                                {
                                    printf("Category(up to 6 characters):");
                                    scanf(" %s", temp->cat);
                                }
                                if(admin_choice=='D')
                                {
                                    printf("Date (DD/MM/YY): ");
                                    scanf(" %s", temp->date);
                                }
                                if(admin_choice=='T')
                                {
                                    printf("Time (HH:MM): ");
                                    scanf(" %s", temp->time);
                                }
                            }
                            while(admin_choice!='B');

                            fprintf(fp2,"%s %s %s %s %s %s\n",temp->name,temp->desc,temp->loc,temp->cat,temp->date,temp->time);
                        }
                    fclose(fp2);
                }

                fclose(fp1);
                remove("Events.txt");

                rename("Change.txt", "Events.txt");

                printf("\nList of events :\n\n");
                view_events();
            }
            else
            {
                i++;
                if(i==m)
                    printf("\nThere is no event with that name!\n");
            }
    }
}*/

void change_event_details()
{
    FILE *fp1, *fp2,*fp3;
    EVENT pom,*temp;
    temp=malloc(sizeof(EVENT));
    char change_event[41],admin_choice;
    int m=0,j=0;
    if((fp1=fopen("Events.txt", "r"))!=0)
    {
        printf("List of all events:\n\n");
        while(fscanf(fp1, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
        {
           write(pom);
            m++;
        }
        rewind(fp1);
        printf("\nPleas ID of the event you wish to change!\n");
        scanf("%s", change_event);
        while(fscanf(fp1, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
            if(strcmp(pom.id,change_event)==0)
            {
                if((fp2=fopen("Change.txt", "w"))!=0)
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s %s %s %s %s %s",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
                        if(strcmp(pom.id, change_event)!=0)
                            fprintf(fp2, "%s %s %s %s %s %s %s\n",pom.id, pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time);
                        else
                        {
                            strcpy(temp->id,pom.id);
                            strcpy(temp->name,pom.name);
                            strcpy(temp->desc,pom.desc);
                            strcpy(temp->loc,pom.loc);
                            strcpy(temp->cat,pom.cat);
                            strcpy(temp->date,pom.date);
                            strcpy(temp->time,pom.time);

                            do
                            {
                                printf("\nWhat would you like to change?\n");
                                printf("\tName [N]\n");
                                printf("\tDescription[O]\n");
                                printf("\tLocation [L]\n");
                                printf("\tCategory [C]\n");
                                printf("\tDate [D]\n");
                                printf("\tTime[T]\n");
                                printf("\tBack [B]\n");
                                scanf(" %c", &admin_choice);
                                if(admin_choice=='N')
                                {
                                    printf("Name (up to 40 characters): ");
                                    scanf(" %s", temp->name);
                                }
                                if(admin_choice=='O')
                                {
                                    printf("Description (up to 500 characters) and instead ' ' write '/' ");
                                    scanf(" %s", temp->desc);
                                }
                                if(admin_choice=='L')
                                {
                                    printf("Location (up to 100 characters): ");
                                    scanf(" %s", temp->loc);
                                }
                                if(admin_choice=='C')
                                {
                                    printf("List of categories: \n");
                                    if((fp3=fopen("Categories.txt","r"))!=0)
                                    {
                                        char categ[7],cat2[7];
                                        int a=0;
                                        while( fscanf(fp3,"%s",categ)!=EOF)
                                            printf("%s\n", categ);

                                        while(a==0)
                                        {
                                            rewind(fp3);

                                            printf("Category(up to 6 characters):\n");
                                            scanf("%s",cat2);
                                            while((fscanf(fp3,"%s",categ)!=EOF) )
                                            {

                                                if(strcmp(categ,cat2)==0)
                                                {
                                                    strcpy(temp->cat,cat2);
                                                    a++;
                                                }
                                            }
                                        }
                                        fclose(fp3);
                                    }
                                }
                                if(admin_choice=='D')
                                {
                                    printf("Date (DD/MM/YY): ");
                                    scanf(" %s", temp->date);
                                }
                                if(admin_choice=='T')
                                {
                                    printf("Time (HH:MM): ");
                                    scanf(" %s", temp->time);
                                }
                            }
                            while(admin_choice!='B');

                            fprintf(fp2,"%s %s %s %s %s %s %s\n",temp->id,temp->name,temp->desc,temp->loc,temp->cat,temp->date,temp->time);
                        }
                    fclose(fp2);
                }

                fclose(fp1);
                remove("Events.txt");

                rename("Change.txt", "Events.txt");

                printf("\nList of events :\n\n");
                view_events();
            }
            else
            {
                j++;
                if(j==m)
                    printf("\nThere is no event with that ID!\n");
            }
    }
}
void write_in_file(int n, EVENT *arr, FILE *fp)// pomocna funkcija
{
    int i;
    for(i=0; i<n; i++)
        fprintf(fp,"%s %s %s %s %s %s %s\n",arr[i].id, arr[i].name, arr[i].desc, arr[i].loc, arr[i].cat, arr[i].date, arr[i].time);
}

void sort_newest_date()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s %s  %s %s",arr[n].id, arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
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
        write_in_file(n, arr, fout);
    fclose(fout);
    printf("\nFile was made with events sorted by newest date!\n");
}


void sort_by_alphabet()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s %s  %s %s",arr[n].id, arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
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
        write_in_file(n, arr, fout);
    fclose(fout);
    printf("\nFile was made with events sorted by alphabet!\n");
}

void sort_oldest_date()
{
    int n=0, c=1000, i, j, h;
    EVENT *arr=(EVENT *)malloc(c*sizeof(EVENT));
    FILE *fout, *fin;
    fin=fopen("Events.txt","r");
    while(fscanf(fin,"%s %s %s %s %s  %s %s",arr[n].id, arr[n].name, arr[n].desc, arr[n].loc, arr[n].cat, arr[n].date, arr[n].time)!=EOF)
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
        write_in_file(n, arr, fout);
    fclose(fout);
    printf("\nFile was made with events sorted by oldest date!\n");
}

/*
void delete_category()
{
    FILE *fp1, *fp2;
    char categ[6],id[10],temp[6];
    int i=0, m=0;
    if((fp1=fopen("Categories.txt", "r"))!=0)
    {
        printf("List of all categories:\n\n");
        while(fscanf(fp1, "%s %s ",categ,id)!=EOF)
        {
            printf("%s ",categ);
            printf("%s \n",id);
            m++;
        }
        rewind(fp1);
        printf("\nPleas name the category you wish to delete!\n");
        scanf("%s", temp);
        while(fscanf(fp1, "%s %s ",categ,id)!=EOF)
            if(strcmp(categ,temp)==0)
            {
                if((fp2=fopen("Replica.txt", "w"))!=0)
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s %s ",categ,id)!=EOF)
                        if(strcmp(categ, temp)!=0)
                            fprintf(fp2, "%s %s \n", categ,id);
                    fclose(fp2);
                }

                fclose(fp1);
                remove("Categories.txt");
                rename("Replica.txt", "Categories.txt");

                printf("\nList of categories after deletin:\n\n");
                rewind(fp2);
                if((fp2=fopen("Categories.txt","r"))!=0)
                {
                    while(fscanf(fp2, "%s %s ",categ,id)!=EOF)
                    {
                        printf("%s ",categ);
                        printf("%s \n",id);

                    }
                    fclose(fp2);
                }
            }
            else
            {
                i++;
                if(i==m)
                    printf("\nThere is no category with that name!\n");

            }
    }
}*/

void delete_category()
{
    FILE *fp1, *fp2;
    char categ[16]= {0},temp[6]= {0};
    int i=0, m=0;
    if((fp1=fopen("Categories.txt", "r"))!=0)
    {
        printf("List of all categories:\n\n");
        while(fscanf(fp1, "%s",categ)!=EOF)
        {
            printf("%s\n",categ);
            m++;
        }
        rewind(fp1);
        printf("\nPleas name the category you wish to delete!\n");
        scanf("%s", temp);
        while(fscanf(fp1, "%s",categ)!=EOF)
            if(strcmp(categ,temp)==0)
            {
                if((fp2=fopen("Replica.txt", "w"))!=0)
                {
                    rewind(fp1);
                    while(fscanf(fp1, "%s",categ)!=EOF)
                        if(strcmp(categ, temp)!=0)
                            fprintf(fp2, "%s \n", categ);
                    fclose(fp2);
                }

                fclose(fp1);
                remove("Categories.txt");
                rename("Replica.txt", "Categories.txt");

                printf("\nList of categories after deletin:\n\n");
                list_categories(fp2);
            }
            else
            {
                i++;
                if(i==m)
                    printf("\nThere is no category with that name!\n");

            }
    }
}
/*
void add_category()
{
    char response, cat_name[15] = {0}, cat_id[6] = {0};
    FILE *fcat = fopen("Categories.txt", "a+");
    printf("\nHere is the current list of categories:\n");
    list_categories(fcat);
    do
    {
        printf("\nAre you sure you want add another category [Y] or [N]:\n");
        scanf(" %c", &response);
        if(response == 'Y')
        {
            printf("Please type the name of the category: ");
            scanf(" %[^\n]",cat_name);
            printf("Add category ID: ");
            scanf(" %[^\n]",cat_id);

            fprintf(fcat, "%s %s\n", cat_name, cat_id);
            fclose(fcat);
        }

        else if (response != 'N')
            printf("Unknown commande!");
    }
    while(response != 'N');
}
*/

void add_category()
{
    char response, cat_name[15] = {0};
    FILE *fcat = fopen("Categories.txt", "a+");
    printf("\nHere is the current list of categories:\n");
    list_categories(fcat);
    do
    {
        printf("\nAre you sure you want add another category [Y] or [N]:\n");
        scanf(" %c", &response);
        if(response == 'Y')
        {
            printf("Please type the name of the category: ");
            scanf(" %[^\n]",cat_name);

            fprintf(fcat, "%s \n", cat_name);

        }

        else if (response != 'N')
        {
            printf("Unknown commande!");

        }
    }
    while(response != 'N');
    fclose(fcat);
}

void guest_view_events(int flag)
{

}
/*
void list_categories()
{
    FILE* fcat = 0;
    char cat_name[15] = {0}, cat_id[6] = {0};
    if((fcat = fopen("Categories.txt", "r"))!= 0)
        while(fscanf(fcat, "%s %s", cat_name, cat_id) != EOF)
            printf("%s %s\n", cat_id, cat_name);
    fclose(fcat);
}*/

void list_categories(FILE* fcat)
{
    char cat_name[15] = {0};
    if((fcat=fopen("Categories.txt", "r"))!=0)
    {
        while(fscanf(fcat, "%s", cat_name)!=EOF)
            printf("%s\n", cat_name);
        fclose(fcat);
    }
}
void events_by_category()
{
    FILE *fevent,*fcat=0;
    EVENT ev;
    int count=0;
    char cat_name[20], view_choice;
    printf("Dogadjaji neke od kategorija [E] or all events?[A]\n");
    scanf(" %c", &view_choice);
    if(view_choice=='E')
    {
        list_categories(fcat);
        printf("Choose a category!\n");
        scanf("%s", cat_name);
        if((fevent=fopen("Events.txt", "r")) != 0)
        {
            while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)

                if(strcmp(cat_name, ev.cat) == 0)
                {
                    count++;
                    write(ev);
                }
            if(count==0)
                printf("\nThere is no events with that category!\n\n");
        }
        fclose(fevent);
    }
    if(view_choice=='A')
        view_events();

}




void quiz()
{
    FILE *fp;
    QUIZ temp;
    int n, i, count=0;
    char quiz_answ[2];
    if((fp=fopen("Quiz.txt", "r"))!=0)
    {
        while(fscanf(fp, "%s %s %s %s %s", temp.question, temp.ans1, temp.ans2, temp.ans3, temp.true_answ)!=EOF)
        {
            printf("\n");

            n=strlen(temp.question);
            for(i=0; i<n; i++)
                if(temp.question[i]=='/')
                    printf(" ");
                else
                    printf("%c",temp.question[i]);
            printf(" ");
            printf("\n");

            n=strlen(temp.ans1);
            for(i=0; i<n; i++)
                if(temp.ans1[i]=='/')
                    printf(" ");
                else
                    printf("%c",temp.ans1[i]);
            printf(" ");
            printf("\n");

            n=strlen(temp.ans2);
            for(i=0; i<n; i++)
                if(temp.ans2[i]=='/')
                    printf(" ");
                else
                    printf("%c",temp.ans2[i]);
            printf(" ");
            printf("\n");

            n=strlen(temp.ans3);
            for(i=0; i<n; i++)
                if(temp.ans3[i]=='/')
                    printf(" ");
                else
                    printf("%c",temp.ans3[i]);
            printf(" ");

            printf("\n\n");

            printf("Answer: ");
            scanf(" %s", &quiz_answ);
            if(strcmp(quiz_answ,temp.true_answ)==0)
            {
                printf ("\nYour answer is true!\n");
                count++;
            }
            else
                printf("\nYour anser is wrong. True answer is %s\n", temp.true_answ );

        }
        fclose(fp);
    }

    if(count<=3)
        printf ("You have %d true answers. Bad knowledge of Rotterdam!\n", count);
    else if (count>3 && count<=7)
        printf("You have %d true answers. Medium knowledge of Rotterdam!\n", count);
    else
        printf ("You have %d true answers. Excellent knowledge of Rotterdam!\n", count);

    printf ("\n");


}

/*
void view_event_details()
{
    FILE *fp;
    EVENT pom;
    char guest_choice, name[50];
    printf("Do you want see details and comment?\n");
    printf("YES[Y] or BACK[B]\n");
    scanf("%c",&guest_choice);
    if(guest_choice=='Y')
    {

        int a=0,n,i;
        if((fp=fopen("Events.txt","r"))!=0)
        {
            while(a==0)
            {
                printf("\nPleas name the event !\n");
                scanf("%s", name);
                rewind(fp);
                while(fscanf(fp, "%s %s %s %s %s %s", pom.name, pom.desc, pom.loc, pom.cat, pom.date, pom.time)!=EOF)
                {
                    if(strcmp(name,pom.name)==0)
                    {
                        n=strlen(pom.name);
                        for(i=0; i<n; i++)
                            if(pom.name[i]=='/')
                                printf(" ");
                            else
                                printf("%c",pom.name[i]);
                        printf(" ");

                        n=strlen(pom.desc);
                        for(i=0; i<n; i++)
                            if(pom.desc[i]=='/')
                                printf(" ");
                            else
                                printf("%c",pom.desc[i]);
                        printf(" ");
                        n=strlen(pom.loc);
                        for(i=0; i<n; i++)
                            if(pom.loc[i]=='/')
                                printf(" ");
                            else
                                printf("%c",pom.loc[i]);
                        printf(" ");
                        printf("%s ",pom.cat);
                        printf("%s ",pom.date);
                        printf("%s",pom.time);
                        printf("\n");
                        a++;
                    }

                }
            }
            fclose(fp);
        }
        printf("Do you want to add or read a comments or back?\n");
        printf("YES[Y] or BACK[B]\n");
        getchar();
        scanf("%c",&guest_choice);
        if(guest_choice=='Y')
        {
            comment();
        }
    }

}*/
void comment(char *fajl)
{
    FILE *f,*fcom;
    char s[15],com[500];
    if((f=fopen(fajl,"a+"))!=0)
    {
        if((fcom=fopen("Novi.txt","w"))!=0)
        {

            while(fgets(s,15,f)!=0)
            {
                printf("%s",s);
                fputs(s,fcom);
            }
            printf("Write a comment\n");
            getchar();
            scanf("%[^\n]s",com);
            fputs(com,fcom);
            fputc('\n',fcom);

            fclose(fcom);
        }
        fclose(f);
    }
    remove("Comment.txt");
    rename("Novi.txt","Comment.txt");
}

void view_todays_events()
{
    FILE *fevent,*fcat=0;
    EVENT ev;
    int count=0,a=0;
    char cat_name[20],id[6];
    struct tm *tm;
    time_t t;
    char str_date[100], guest_choice;
    t=time(NULL);
    tm = localtime(&t);
    strftime(str_date, sizeof(str_date), "%d/%m/%Y", tm);
    list_categories(fcat);
    printf("Izaberite kategoriju!\n");
    scanf("%s", cat_name);
    printf("\n");
    if((fevent=fopen("Events.txt", "r"))!=0)
    {
        while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)

            if(strcmp(str_date, ev.date)==0 && strcmp(cat_name, ev.cat)==0)
            {
                count++;
              write(ev);
                printf("Do you want choose option comment?\n");
                printf("YES[Y] or BACK[B]\n");
                scanf(" %c",&guest_choice);
                if(guest_choice=='Y')

                    {
                         if((fevent=fopen("Events.txt", "r"))!=0)
        {
             while(a==0)
            {
                printf("\nPleas ID of the event !\n");
                scanf("%s", id);
                rewind(fevent);
            while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
                if(strcmp(str_date, ev.date)==0 && strcmp(cat_name, ev.cat)==0 && (strcmp(id,ev.id)==0))
                    {
                        write(ev);
                        a++;
                    }
        }
        fclose(fevent);
    }
    char dat[]={"_FAJL.txt"},*ime=0;
            ime=strcat(id,dat);
            comment(ime);
                    }

            }
        if(count==0)
            printf("\nThere is no todays events!\n\n");
    }
    fclose(fevent);

}

void view_past_events()
{
    FILE *fevent,*fcat=0;
    EVENT ev;
    int count=0,a=0;
    struct tm *tm;
    time_t t;
    char str_date[100], cat_name[20], guest_choice,id[6];
    t=time(NULL);
    tm = localtime(&t);
    list_categories(fcat);
    printf("Izaberite kategoriju!\n");
    scanf("%s", cat_name);
    printf("\n");
    strftime(str_date, sizeof(str_date), "%d/%m/%Y", tm);
    if((fevent=fopen("Events.txt", "r"))!=0)
    {
        while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
            if(strcmp(str_date, ev.date)>0 && strcmp(ev.cat, cat_name)==0)
            {
                count++;
               write(ev);
            }
                  if(count==0)
            printf("\nThere is no past events!\n\n");
    }
    fclose(fevent);

                printf("Do you want choose option comment?\n");
                printf("YES[Y] or BACK[B]\n");
                scanf(" %c",&guest_choice);
                if(guest_choice=='Y')
                    {
                         if((fevent=fopen("Events.txt", "r"))!=0)
                    while(a==0)
                    {
                        printf("\nPleas ID of the event !\n");
                        scanf("%s", id);
                        rewind(fevent);
                        while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
                            if(strcmp(str_date, ev.date)>0 && strcmp(ev.cat, cat_name)==0&& (strcmp(id,ev.id)==0))
                            {
                                write(ev);
                                a++;
                            }
                    }
                    fclose(fevent);

                char dat[]={"_FAJL.txt"},*ime=0;
            ime=strcat(id,dat);
            comment(ime);
                    }

}

void view_future_events()
{
    FILE *fevent,*fcat=0;
    EVENT ev;
    int count=0;
    struct tm *tm;
    time_t t;
    char str_date[100], cat_name[20], guest_choice,id[6];
    t=time(NULL);
    tm = localtime(&t);
    list_categories(fcat);
    printf("Izaberite kategoriju!\n");
    scanf("%s", cat_name);
    printf("\n");
    strftime(str_date, sizeof(str_date), "%d/%m/%Y", tm);
    if((fevent=fopen("Events.txt", "r"))!=0)
    {
        while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)

            if(strcmp(str_date, ev.date)<0 && strcmp(ev.cat, cat_name)==0)
            {
                count++;
               write(ev);
            }
              if(count==0)
            printf("\nThere is no future events!\n\n");
    }
    fclose(fevent);
                printf("Do you want chose option comment?\n");
                printf("YES[Y] or BACK[B]\n");
                scanf(" %c",&guest_choice);
                if(guest_choice=='Y')
                {

         int a=0;
        if((fevent=fopen("Events.txt", "r"))!=0)
        {
             while(a==0)
            {
                printf("\nPleas ID of the event !\n");
                scanf("%s", id);
                rewind(fevent);
            while(fscanf(fevent, "%s %s %s %s %s %s %s",ev.id, ev.name, ev.desc, ev.loc, ev.cat, ev.date, ev.time)!=EOF)
                if(strcmp(str_date, ev.date)<0 && strcmp(ev.cat, cat_name)==0 && (strcmp(id,ev.id)==0))
                    {
                        write(ev);
                        a++;
                    }
        }
        fclose(fevent);
    }
    char dat[]={"_FAJL.txt"},*ime=0;
            ime=strcat(id,dat);
            comment(ime);
                }

}




