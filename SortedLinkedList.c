#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable : 4996)

typedef struct Item
{
    int num;
    struct Item* next;
    struct Item* prev;
}Item;

Item* head = NULL;
Item* tail = NULL;
int itemCount = 0;



void printLinkedList()
{
    Item* currentL = head;
    Item* printL;
    int count = 1;
    while (currentL != NULL)
    {
        printL = currentL;
        currentL = currentL->next;
        printf("#%d - num = %d\n", count, printL->num);
        count++;
    }
    printf("Items in queue: %d\n", itemCount);
}

void freeLinkedList()
{
    Item* currentL = head;
    Item* releaseL;
    while (currentL != NULL)
    {
        releaseL = currentL;
        currentL = currentL->next;
        free(releaseL);
    }
}
void addItem(int num)
{
    Item* currentI;
    currentI = (Item*)malloc(sizeof(Item));
    currentI->num = num;
    currentI->next = NULL;
    if (head == NULL)
    {
        head = currentI;
        tail = currentI;
        currentI->prev = NULL;
        itemCount++;
    }
    else
    {
        currentI->prev = tail;
        tail->next = currentI;
        tail = currentI;
        itemCount++;
    }
}

void Swap(Item* Address)
{
    if (Address == NULL || Address->next == NULL)
    {
        return;
    }
    Item* temp = (Item*)malloc(sizeof(Item));
    temp->next = Address->next->next;
    temp->prev = Address->next;
    Address->next->next = Address;
    Address->next->prev = Address->prev;
    Address->next = temp->next;
    Address->prev = temp->prev;
    free(temp);

    // if the item changed was the head
    if (Address->prev->prev == NULL)
    {
        head = Address->prev;
    }

    else
    {
        Address->prev->prev->next = Address->prev;
    }
    // if the item is now the tail
    if (Address->next == NULL)
    {
        tail = Address;
    }
    else
    {
        Address->next->prev = Address;
    }
}

void bubbleSort()
{
    Item* currentL = NULL;
    int swaps = 1;
    if (head == NULL)
    {
        return;
    }
    do
    {
        currentL = head;
        swaps = 0;
        while (currentL != NULL)
        {
            if (currentL->next && currentL->num > currentL->next->num)
            {
                Swap(currentL);
                swaps = 1;
            }
            currentL = currentL->next;
        }
    } while (swaps != 0);
    printf("list is now sorted\n\n");
}

void log(char message[1000]) {
    // time stamps for the log file
    time_t t;
    time(&t);
    char strTime[100];
    struct tm* timeinfo;
    timeinfo = localtime(&t);

    sprintf(strTime, "%d:%d:%d - %s", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
    FILE* f = fopen("logs.log", "a");
    fputs(strTime, f);
    fclose(f);
}
// log error function
void LogError(char message[100]) {
    char Error[100] = "Error - ";
    strcat(Error, message);
    log(Error);
}
// log event function
void LogEvent(char message[100]) {
    char event[100] = "Event - ";
    strcat(event, message);
    log(event);
}
int num;

int main()
{

    LogEvent("Program start running\n");
    time_t i = time(NULL);
    double start = time(&i);
    srand(i);
    char str[1000];
    for (int j = 0; j < 100000; j++) {
        num = rand() % 100;
        addItem(num);
        sprintf(str, "%s - %d, %s - %d%s", "Random number entered to list head", num, "item count", j, "\n");
        LogEvent(str);
        strcpy(str, "");
    }
    printf("List before sorting:\n");
    printLinkedList();
    LogEvent("List printed to console\n");
    bubbleSort();
    LogEvent("List sorted\n");
    printf("List after sorting:\n");
    printLinkedList();
    LogEvent("sorted List printed to console\n");
    freeLinkedList();
    LogEvent("List freed\n");
    LogEvent("Program ended\n");
    double end = time(&i);
    sprintf(str, "%s - %lf", "Running time in seconds", end - start);
    LogEvent(str);

    return 0;
}
