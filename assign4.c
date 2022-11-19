#include <stdio.h>

void create();
void update();
void read();
void delete ();

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

        char inputStr[10];
        gets(inputStr);
        char input;
        sscanf(inputStr, "%c", &input);

        switch (input)
        {

        case 'C':
        case 'c':
            create();
            break;

        case 'U':
        case 'u':
            printf("TODO: update\n");
            update();
            break;

        case 'R':
        case 'r':
            read();
            break;

        case 'D':
        case 'd':
            printf("TODO: delete\n");
            delete ();
            break;

        default:
            printf("ERROR: invalid option\n");
        }
    }

    return 0;
}

void create()
{
    printf("Enter a CS course number:\n");
    char courseNumberStr[4];
    gets(courseNumberStr);
    int courseNumber;
    sscanf(courseNumberStr, "%i", &courseNumber);

    Course course;
    printf("Enter a CS course name:\n");
    gets(course.course_Name);

    printf("Enter a CS course schedule:\n");
    gets(course.course_Sched);

    printf("Enter a CS course credit hours:\n");
    char courseHours[10];
    gets(courseHours);
    sscanf(courseHours, "%i", &course.course_Hours);

    printf("Enter a CS course enrollment:\n");
    char courseSize[10];
    gets(courseSize);
    sscanf(courseSize, "%i", &course.course_Size);

    FILE *courses = fopen("./courses.dat", "wb");

    fseek(courses, courseNumber * sizeof(Course), 0);

    long recordsWritten = fwrite(&course, sizeof(Course), 1L, courses);

    fclose(courses);
}

void update() {}

void read()
{
    printf("Enter a CS course number:\n");
    char courseNumberStr[10];
    gets(courseNumberStr);
    int courseNumber;
    sscanf(courseNumberStr, " %d", &courseNumber);


    FILE *courses = fopen("./courses.dat", "rb");
    Course course;
    fseek(courses, courseNumber * sizeof(Course), 0);
    int read = fread(&course, sizeof(Course), 1L, courses);
    fclose(courses);

    printf("Course number: %i\n", courseNumber);
    printf("Course name: %s\n", course.course_Name);
    printf("Scheduled days: %s\n", course.course_Sched);
    printf("Credit hours: %i\n", course.course_Hours);
    printf("Enrolled Students: %i\n", course.course_Size);

}

void delete () {}