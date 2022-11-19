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

        char response[1];
        gets(response);
        char input = response[0];

        switch (input)
        {

        case 'C':
        case 'c':
            printf("TODO: Create\n");
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
            delete();
            break;

        default:
            printf("ERROR: invalid option\n");
        }
    }

    return 0;
}

void create() {}
void update() {}

void read()
{
    printf("Enter a CS course number:\n");
    int courseNumber;
    scanf("%i", &courseNumber);

    FILE *courses = fopen("./courses.dat", "rb");

    Course course;
    fseek(courses, courseNumber * sizeof(Course), 0);
    int read = fread(&course, sizeof(Course), 1L, courses);

    printf("Course number: %i\n", courseNumber);
    printf("Course name: %s\n", course.course_Name);
    printf("Scheduled days: %s\n", course.course_Sched);
    printf("Credit hours: %i\n", course.course_Hours);
    printf("Enrolled Students: %i\n", course.course_Size);

    fclose(courses);
}

void delete () {}