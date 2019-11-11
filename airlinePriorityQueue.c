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


int main()
{
    struct passenger airline[20];
    parseFile(airline);
    printf("first mileage is %d", airline[0].mileage);
    return 0;
}
