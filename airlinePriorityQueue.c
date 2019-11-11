#include "stdio.h"
#include "stdlib.h"


struct passenger
{
    char name[50];
    int mileage;
    int years;
    int sequence;
    int priorityNum;
};

void readFile()
{
    char str[10000];
    FILE * file;
    file = fopen("customers.txt", "r");
    if(file)
    {
        while(fscanf(file, "%s", str)!=EOF)
            printf("%s\n", str);
        fclose(file);
    }
}


int main()
{
    readFile();
    return 0;
}
