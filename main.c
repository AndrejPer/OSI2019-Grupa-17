#include <stdio.h>
#include <stdlib.h>


typedef struct event
{
    char name[101] ;
    char desc[501]; //description
    char loc[101]; //location
    int cat[6]; //5-cipher ID of the category
    char date[9];
    char time[6];
    char id[6]; //5-character id of the event
} EVENT;

void citaj(EVENT *);
int main(int argc, char *argv[])
{
    int i, n;
    EVENT *niz;
    FILE *dat;
    do
        printf("n="), scanf("%d", &n);
    while (n < 1);
    niz = (EVENT *)malloc(n * sizeof(EVENT));
    for (i = 0; i < n; i++)
        printf("%d. Event:\n", i + 1), citaj(niz + i);
    if (dat = fopen("Events.dat", "wb"))
    {
        fwrite(niz, sizeof(EVENT), n, dat);
        fclose(dat);
    }
    free(niz);
    return 0;
}



void citaj(EVENT *event)
{
    printf("  Event name: ");
    scanf(" %[^\n]", event->name);
    printf("  Description: ");
    scanf(" %[^\n]", event->desc);
    printf("  Location: ");
    scanf(" %[^\n]", event->loc);
    printf("  Category ID: ");
    scanf("%d", &event->cat);
    printf("  Date: ");
    scanf(" %[^\n]", event->date);
    printf("  Time: ");
    scanf(" %[^\n]", event->time);
    printf("  Event ID: ");
    scanf(" %[^\n]", event->id);

}
