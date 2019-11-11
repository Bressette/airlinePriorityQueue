#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct passenger
{
    char name[50];
    int mileage;
    int years;
    int sequence;
    int priorityNum;
};


void heapify(struct passenger airline[], int size, int rootIndex)
{
    int largest = rootIndex;
    int left = rootIndex*2 + 1;
    int right = rootIndex*2 + 2;

    if(left < size && airline[left].priorityNum < airline[largest].priorityNum)
    {
        largest = left;
    }

    if(right < size && airline[right].priorityNum < airline[largest].priorityNum)
    {
        largest = right;
    }

    if(largest != rootIndex)
    {
        struct passenger temp = airline[largest];
        airline[largest] = airline[rootIndex];
        airline[rootIndex] = temp;
        heapify(airline, size, largest);
    }
}


//Build a min heap from current array
//Replace the root with the last item in the array
//Decrease the size of the heap by one
//Repeat while size of heap is greater than one
void heapSort(struct passenger airline[], int size)
{
    for(int i = size / 2 - 1; i >= 0; i--)
        heapify(airline, size, i);

    for(int i = size - 1; i >= 0; i--)
    {
        struct passenger temp = airline[0];
        airline[0] = airline[i];
        airline[i] = temp;

        heapify(airline, i, 0);
    }
}



void parseFile(struct passenger airline[])
{
    int line_index = 0;
    char str[100];
    FILE * file;
    file = fopen("customers.txt", "r");
    char *subString;


    while(fgets(str, 100, file)!=NULL)
    {
        subString = strtok(str, "\t");
        strcpy(airline[line_index].name, subString);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].mileage);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].years);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].sequence);

        line_index++;
    }

    fclose(file);
}

void printPassData(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\n", airline[i].name, airline[i].mileage, airline[i].years, airline[i].sequence, airline[i].priorityNum);
    }
}

void genPriorityNum(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        airline[i].priorityNum = (airline[i].mileage/1000) + airline[i].years - airline[i].sequence;
    }

}

void printPassPriority(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        printf("Name: %s -> Priority: %d\n", airline[i].name, airline[i].priorityNum);
    }
}


int main()
{
    int numPassengers = 15;
    struct passenger airline[numPassengers];
    parseFile(airline);
    genPriorityNum(airline, numPassengers);
    heapSort(airline, numPassengers);
    printPassPriority(airline, numPassengers);

    return 0;
}
