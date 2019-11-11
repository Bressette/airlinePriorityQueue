#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//struct that holds all passenger data
struct passenger
{
    char name[50];
    int mileage;
    int years;
    int sequence;
    int priorityNum;
};


//function that turns a passenger array into a minimum binary heap based on priority number
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


//function that uses heapSort to sort a passenger array into decreasing order
//based on priority number to generate the priority queue
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


/*function that parses a file customers.txt and populates a passenger array
 *with the contents of the text file. The file is parsed line by line using fgets
 *and strtok is used to generate a substring for each field that will be stored in
 *the passenger struct
 */
void parseFile(struct passenger airline[])
{
    //variable to store what line is being processed
    int line_index = 0;

    //variable that holds the contents of a line
    char str[100];

    //file that is used to read customers.txt
    FILE * file;
    file = fopen("customers.txt", "r");
    //variable used to store a substring to be stored into passenger
    char *subString;

    //loop that iterates through the file line by line storing data fields into passenger
    while(fgets(str, 100, file)!=NULL)
    {
        //copies the name data field into passenger.name
        subString = strtok(str, "\t");
        strcpy(airline[line_index].name, subString);

        //stores mileage field as a string
        subString = strtok(NULL, str);
        strtok(subString, "\t");
        //converts mileage string into an integer
        sscanf(subString, "%d", &airline[line_index].mileage);

        //stores years field as a string
        subString = strtok(NULL, str);
        strtok(subString, "\t");
        //converts years string into an integer
        sscanf(subString, "%d", &airline[line_index].years);

        //stores sequence field as a string
        subString = strtok(NULL, str);
        strtok(subString, "\t");
        //converts sequence string into an integer
        sscanf(subString, "%d", &airline[line_index].sequence);

        //increments line_index so that the next line can be processed
        line_index++;
    }

    fclose(file);
}


//function used to validate that the text file is read properly displaying all data fields in passenger
void printPassData(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        printf("%s\t%d\t%d\t%d\t%d\n", airline[i].name, airline[i].mileage, airline[i].years, airline[i].sequence, airline[i].priorityNum);
    }
}


//function that generates the priority number for each passenger
void genPriorityNum(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        airline[i].priorityNum = (airline[i].mileage/1000) + airline[i].years - airline[i].sequence;
    }

}


//function to print the name of each passenger along with their priority number
void printPassPriority(struct passenger airline[], int numPassengers)
{
    for(int i = 0; i < numPassengers; i++)
    {
        printf("Name: %s -> Priority: %d\n", airline[i].name, airline[i].priorityNum);
    }
}


int main()
{
    //variable that holds number of passengers
    int numPassengers = 15;
    struct passenger airline[numPassengers];

    //stores the values from the text file customers.txt into airline
    parseFile(airline);

    //generates priority numbers for airline and stores them
    genPriorityNum(airline, numPassengers);

    //sorts the passengers based on priority numbers in descending order
    heapSort(airline, numPassengers);

    //prints the name and priority number of each passenger
    printPassPriority(airline, numPassengers);
    return 0;
}

