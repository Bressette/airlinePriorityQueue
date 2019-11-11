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
    int curNumEle;
    int heapSize;
};

struct maxHeap
{
    struct passenger *airline;
    int curNumEle;
    int heapSize;
};


void heapify(struct maxHeap heap, int curIndex)
{
    int largest = curIndex;
    int left = 2*curIndex + 1;
    int right = 2*curIndex + 2;

    if(left < heap.curNumEle && heap.airline[left].priorityNum > heap.airline[largest].priorityNum)
        largest = left;
    if(right < heap.curNumEle && heap.airline[right].priorityNum > heap.airline[largest].priorityNum)
        largest = right;
    if(largest != curIndex)
    {
        struct passenger temp = heap.airline[curIndex];
        heap.airline[curIndex] = heap.airline[largest];
        heap.airline[largest] = temp;

        heapify(heap, largest);
    }
}

struct maxHeap insertHeap(struct maxHeap heap, struct passenger airlineData[])
{
    for(int j = 0; j < heap.heapSize; j++)
    {
    if(heap.heapSize == heap.curNumEle)
    {
        printf("The heap is full\n");
        return heap;
    }

    else
    {
        heap.airline[heap.curNumEle] = airlineData[heap.curNumEle];
        heap.curNumEle++;

        for(int i = heap.curNumEle/2-1; i >= 0; i--)
            heapify(heap, i);
        return heap;
    }
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
        printf("Printing substring %s\n", subString);
        strcpy(airline[line_index].name, subString);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].mileage);
        printf("Printing substring %s\n", subString);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].years);
        printf("Printing substring %s\n", subString);

        subString = strtok(NULL, str);
        strtok(subString, "\t");
        sscanf(subString, "%d", &airline[line_index].sequence);
        printf("Printing substring %s\n", subString);

        line_index++;
    }

    fclose(file);
}

printPassData(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\n", airline[i].name, airline[i].mileage, airline[i].years, airline[i].sequence, airline[i].priorityNum);
    }
}

genPriorityNum(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        airline[i].priorityNum = (airline[i].mileage/1000) + airline[i].years - airline[i].sequence;
    }

}

int main()
{
    int numPassengers = 15;
    struct passenger airline[numPassengers];
    parseFile(airline);
    genPriorityNum(airline, numPassengers);
    printPassData(airline, numPassengers);
    printf("first mileage is %d", airline[0].mileage);

    struct maxHeap priorityHeap;
    priorityHeap.heapSize = numPassengers;
    priorityHeap.airline = malloc(sizeof(struct passenger)*(priorityHeap.heapSize));
    priorityHeap.curNumEle = 0;
    insertHeap(priorityHeap, airline);

    return 0;
}
