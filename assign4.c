#include <stdio.h>
#include <string.h>

typedef struct
{
    char course_Name[80];
    char course_Sched[4];
    unsigned course_Hours;
    unsigned course_Size;
    unsigned padding;
} Course;

void create();
void update();
void read();
void delete ();
int getCourseExists(int courseNumber);
Course getCourse(int courseNumber);

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

    if (getCourseExists(courseNumber)){
        printf("ERROR: course already exists\n");
        return;
    }

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

    Course course = getCourse(courseNumber);

    if (getCourseExists(courseNumber)){
        printf("Course number: %i\n", courseNumber);
        printf("Course name: %s\n", course.course_Name);
        printf("Scheduled days: %s\n", course.course_Sched);
        printf("Credit hours: %i\n", course.course_Hours);
        printf("Enrolled Students: %i\n", course.course_Size);
    } else {
        printf("ERROR: course not found\n");
    }

}

void delete () {
    printf("Enter a course number:\n");
    char courseNumberStr[4];
    gets(courseNumberStr);
    int courseNumber;
    sscanf(courseNumberStr, "%i", &courseNumber);


    if (getCourseExists(courseNumber)){
        // delete course
    } else {
        printf("ERROR: course not found\n");
    }
}


// Helpers

Course getCourse(int courseNumber){
    FILE *courses = fopen("./courses.dat", "rb");
    fseek(courses, courseNumber * sizeof(Course), 0);
    Course course;
    int read = fread(&course, sizeof(Course), 1L, courses);
    fclose(courses);

    return course;
}

int getCourseExists(int courseNumber){    
    Course course = getCourse(courseNumber);
    if (strlen(course.course_Name) > 0){
        return 1;
    } else {
        return 0;
    }
}