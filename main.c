#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

int minute=0, second=0, flag=0, endtime=0, totaltime=0, exit1=0;
char song_name[50];

struct Song
{
    int min,sec;
    char name[50];
    struct Song *next;
    struct Song *prev;
}*head,*temp1;

void delay(ms)
{
    clock_t timeDelay = ms + clock();
    while(timeDelay>clock());
}

void counter()
{
    while(!kbhit() && flag==0)
    {
        if(second > 59)
        {
            second = 0;
            minute++;
        }
        printData();
        delay(1000);
        second++;
        totaltime++;


    if(totaltime>endtime)
    {
            if(temp1->next!=NULL)
            {
                temp1=temp1->next;
                totaltime=0;
                endtime = ((temp1->min)*60) + temp1->sec;
                minute=0;
                second=0;
            }
            else
            {
                flag=1;
                exit1=1;
                totaltime=0;
            }
    }


    }
    selection();

}

void printData()
{
    system("cls");
    printf("1.Play\n2.Pause\n3.Next\n4.Previous\n5.Exit to main menu\n");
    printf("********************************************************\n");
    printf("Now Playing: %s \n", temp1->name);
    printf(" %2d : %2d",minute,second);
    printf("\n********************************************************");
}

void selection()
{
    switch(getch())
    {
    case '1':
        flag=0;
        break;

    case '2':
        flag=1;
        break;

    case '3':
        if(temp1->next!=NULL)
        {
            temp1=temp1->next;
            minute=0;
            second=0;
            endtime = ((temp1->min)*60) + temp1->sec;
            totaltime=0;
            flag=0;
            printData();
        }
        else
        {
            exit1=1;
        }
        break;

    case '4':
        if(temp1->prev!=NULL)
        {
            temp1=temp1->prev;
            endtime=
            minute=0;
            second=0;
            endtime = ((temp1->min)*60) + temp1->sec;
            totaltime=0;
            flag=0;
        }
        else
        {
            exit1=1;
        }
        break;

    case '5':
        flag=1;
        exit1=1;
        totaltime=0;
        break;
    }
}

void play()
{
    if(head==NULL)
    {
        printf("No songs in the playlist!");
    }
    else
    {
        exit1=0;
        flag=0;
        temp1=head;
        totaltime=0;
        endtime = ((temp1->min)*60) + temp1->sec;
        minute=0;
        second=0;
        while(exit1!=1)
        {
            counter();
        }

    }
}

int main()
{
    int choice = 0;
    int i;
    struct Song *temp,*newSong,*pre;
    char name_song[50];
    int a=1;

    while(choice!=5)
    {
        printf("\nPlease select an option:\n");
        printf("1. Play\n");
        printf("2. Display Playlist\n");
        printf("3. Add a song\n");
        printf("4. Delete a song\n");
        printf("5. Power off\n");
        printf("Choice: ");
        scanf(" %d", &choice);

        switch(choice)
        {
        case 1:
            play();
            break;

        case 2:
            if(head==NULL)
            {
                printf("No songs in the playlist!");
            }
            else
            {
                temp = head;
                a = 1;
                while(temp!=NULL)
                {
                    printf("%d. %s\n", a, temp->name);
                    temp=temp->next;
                    a++;
                }
            }
            break;

        case 3:
            newSong=(struct Song*)malloc(sizeof(struct Song));
            printf("Enter the name of the song: ");
            scanf(" %s", newSong->name);
            printf("Enter duration of the song (Minutes Seconds) : ");
            scanf(" %d %d", &(newSong->min), &(newSong->sec));
            temp = head;
            if(temp==NULL)
            {
                head = newSong;
                head->next = NULL;
                head->prev = NULL;
                printf("Song successfully added!");
            }
            else
            {
                temp = head;
                while(temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newSong;
                newSong->prev = temp;
                newSong->next = NULL;
                printf("Song successfully added!");
            }
            break;

        case 4:
            temp = head;
            if (temp == NULL)
            {
                printf("Playlist is empty!");
            }
            else
            {
                printf("Enter the name of the song to be deleted: ");
                scanf(" %s", name_song);

                while(temp!=NULL && ((strcmp(name_song, temp->name)) != 0) )
                {
                    pre=temp;
                    temp=temp->next;
                }

                if(temp->next==NULL && temp->prev==NULL)
                {
                    free(temp);
                    head=NULL;
                    printf("%s successfully deleted!\n", name_song);
                }
                else if(temp==NULL)
                {
                    printf("No song by the name %s exists in the playlist!", name_song);
                }
                else if(temp==head)
                {
                    head = temp->next;
                    free(temp);
                    printf("%s successfully deleted!\n", name_song);
                }
                else if(temp->next==NULL)
                {
                    free(temp);
                    pre->next=NULL;
                    printf("%s successfully deleted!\n", name_song);
                }
                else
                {
                    pre->next = temp->next;
                    temp->next->prev = pre;
                    free(temp);
                    printf("%s successfully deleted!\n", name_song);
                }
            }
            break;

        case 5:
            printf("!POWER OFF!");
            break;

        default:
            printf("Invalid Choice");
        }
    }


    return 0;
}
