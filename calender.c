/*

6. Calendar
The program must have (at least) following operations:
1. initialize (empty the database)
2. save database to file
3. read database from file
4. add an event: user enters description, date, time and duration of an event
5. remove an event

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>


#define SIZE 100
#define MAX_SIZE 1000

struct calendar
{
    char date[SIZE];
    char description[MAX_SIZE];
    char duration[SIZE];
    char time[SIZE];

    struct calendar *next;
    struct calendar *previous;
} *start = NULL, *end = NULL;

void initialize();
void save();
void read();
void add();
void delete ();

char filename[] = {"input.dat"};

int main()
{
    int option;
    while (1)
    {
        system("clear");
        printf("================== calendar Management =============\n\n");
        printf("=============Please choose the following option=========\n\n");
        printf("[1]: Initialize (empty the database)\n");
        printf("[2]: Add an event to a file \n");
        printf("[3]: Read database from file\n");
        printf("[5]: Remove an event\n");
       
        printf("[0]: Exit\n");
        printf("========================================================\n\n");
        printf("\nPlease enter your Choice: \n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            initialize();
            break;

        case 2:
            save();
            break;

        case 3:
            read();
            break;

        case 4:
            add();
            break;

        case 5:
            delete ();
            break;

        case 0:
        exit(0);
        }
    }
}

void initialize()
{
    struct calendar *new_event, *current_event, *display;
    int number_of_event;

    printf("Enter number of events for the calendar: \n");
    scanf("%d", &number_of_event);
    system("cls");

    for (int i = 0; i < number_of_event; i++)
    {
        new_event = (struct calendar *)malloc(sizeof(struct calendar));

        if (new_event == NULL)
        {
            printf("\nMemory Does Not Created.\n");
            exit(0);
        }
        else
        {
            printf("============ Event Details ==========\n");
            printf("Enter Description: \n");
            fflush(stdin);
            scanf("\n\tDescription: %s", new_event->description);

            printf("Enter Date: \n");
            fflush(stdin);
            scanf("\n\tDate: %s", new_event->date);

            printf("Enter Time: \n");
            fflush(stdin);
            scanf("\n\tTime: %s", new_event->time);

            printf("Enter Duration: \n");
            fflush(stdin);
            scanf("\n\tDuration: %s\n", new_event->duration);
        }
        new_event->next = NULL;
        new_event->previous = NULL;

        if (start == NULL && end == NULL)
        {
            start = new_event;
            end = new_event;
            current_event = new_event;
        }
        else
        {
            current_event->next = new_event;
            new_event->previous = current_event;
            current_event = new_event;
            end = new_event;
        }
    }
        if(new_event == NULL)
        {
            printf("Your event is empty!\n");
        }
        else
        {
            display = current_event;
            while(display!=NULL)
            {
                printf("Description: %s\n", display->description);
                printf("Date: %s\n", display->date);
                printf("Time: %s\n", display->time);
                printf("Duration: %s\n",display->duration);
                display = display->next;
            }
        }
}

void save()
{
    struct calendar *new_event, *current_event;
    int number_of_event;

    printf("Enter number of events for the calendar: \n");
    scanf("%d", &number_of_event);
    system("cls");

    for (int i = 0; i < number_of_event; i++)
    {
        new_event = (struct calendar *)malloc(sizeof(struct calendar));

        if (new_event == NULL)
        {
            printf("\nMemory Does Not Created.\n");
            exit(0);
        }
        else
        {
            FILE *file = fopen(filename, "ab");

            if (file == NULL)
            {
                printf("File does not create.\n");
            }
            else
            {   
                printf("Enter Description: \n");
                fflush(stdin);
                gets(new_event->description);
                fprintf(file, "Description: %s", new_event->description);

                printf("Enter Date [yyyy.mm.dd]: \n");
                fflush(stdin);
                gets(new_event->date);
                fprintf(file, "\t\tDate: %s", new_event->date);

                printf("Enter Time [hh:mm]: \n");
                fflush(stdin);
                gets(new_event->time);
                fprintf(file, "\tTime: %s", new_event->time);

                printf("Enter Duration [hh:mm]: \n");
                fflush(stdin);
                gets(new_event->duration);
                fprintf(file, "\tDuration: %s\n", new_event->duration);

                fclose(file);
                fopen(filename, "ab");
            }
            new_event->next = NULL;
            new_event->previous = NULL;

            if (start == NULL && end == NULL)
            {
                start = new_event;
                end = new_event;
                current_event = new_event;
            }
            else
            {
                current_event->next = new_event;
                new_event->previous = current_event;
                current_event = new_event;
                end = new_event;
            }
        }
    }
}

void read()
{
    FILE *in_file = fopen(filename, "rb");
    if (!in_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, in_file);

    printf("read data: %s\n", file_contents);
    fclose(in_file);

    free(file_contents);
    exit(EXIT_SUCCESS);
}

void add()
{
    struct calendar *new_event, *current_event;
    new_event = (struct calendar *)malloc(sizeof(struct calendar));

    if (new_event == NULL)
    {
        printf("\nMemory Does Not Created.\n");
        exit(0);
    }
    else
    {
        FILE *file = fopen(filename, "ab");
        if (file == NULL)
        {
            printf("File does not create.\n");
        }
        else
        {
            printf("Event Details\t");
            fprintf(file, "Event Details :\t");

            printf("Enter Description: \n");
            fflush(stdin);
            gets(new_event->description);
            fprintf(file, "\tDescription: %s", new_event->description);

            printf("Enter Date: \n");
            fflush(stdin);
            gets(new_event->date);
            fprintf(file, "\tDate: %s", new_event->date);

            printf("Enter Time: \n");
            fflush(stdin);
            gets(new_event->time);
            fprintf(file, "\tTime: %s", new_event->time);

            printf("Enter Duration: \n");
            fflush(stdin);
            gets(new_event->duration);
            fprintf(file, "\tDuration: %s\n", new_event->duration);
            fclose(file);
            fopen(filename, "ab");
        }
    }
    new_event->next = NULL;
    new_event->previous = NULL;

    current_event = end;
    current_event->next = new_event;
    new_event->previous = current_event;
    end = new_event;
}

void delete ()
{
   FILE *fp1, *fp2;
        char c;
        int del_line, temp = 1;
        
        fp1 = fopen(filename, "rb");
        c = getc(fp1);
        //until the last character of file is obtained
        while (c != EOF)
        {
          printf("%c", c);
          //print current character and read next character
          c = getc(fp1);
        }
        //rewind
        rewind(fp1);
        printf(" \n Enter line number of event to be deleted:");
        //accept number from user.
        scanf("%d", &del_line);
        //open new file in write mode
        fp2 = fopen("copy.c", "wb");
        c = getc(fp1);
        while (c != EOF) {
          c = getc(fp1);
          if (c == '\n')
          temp++;
          //except the line to be deleted
          if (temp != del_line)
          {
            //copy all lines in file copy.c
            putc(c, fp2);
          }
        }
        //close both the files.
        fclose(fp1);
        fclose(fp2);
        //remove original file
        remove(filename);
        //rename the file copy.c to original name
        rename("copy.c", filename);
        printf("\n The contents of file after being modified are as  follows:\n");
        fp1 = fopen(filename, "rb");
        c = getc(fp1);
        while (c != EOF) {
            printf("%c", c);
            c = getc(fp1);
        }
        fclose(fp1);
}

