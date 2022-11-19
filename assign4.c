#include <stdio.h>

typedef struct
{
    char course_Name[80];
    char course_Sched[4];
    unsigned course_Hours;
    unsigned course_Size;
    unsigned padding;
} Course;

int main()
{
    while (1)
    {

        printf("Enter one of the following actions or press CTRL-D to exit.\n");
        printf("C - create a new course record\n");
        printf("U - update an existing course record\n");
        printf("R - read an existing course record\n");
        printf("D - delete an existing course record\n");

        char response[1];
        gets(response);
        char input = response[0];

        printf("your char is %c", input);

        switch (input)
        {

        case 'C':
        case 'c':
            printf("you hit c block\n");
            break;

        case 'U':
        case 'u':
            printf("you hit u block\n");
            break;

        case 'R':
        case 'r':
            printf("you hit r block\n");
            break;

        case 'D':
        case 'd':
            printf("you hit d block\n");
            break;

        default:
            printf("ERROR: invalid option\n");
        }
    }
    
    return 0;
}