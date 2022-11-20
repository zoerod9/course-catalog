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
void createCourse(int courseNumber, Course course);
Course promptForCourse();
int promptForCourseNumber();
Course getEmptyCourse();

void printCourse(Course course);
void printCourseNumber(int courseNumber);

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
            update();
            break;

        case 'R':
        case 'r':
            read();
            break;

        case 'D':
        case 'd':
            delete();
            break;

        default:
            printf("ERROR: invalid option\n");
        }
    }

    return 0;
}

void create()
{
    int courseNumber = promptForCourseNumber();

    if (getCourseExists(courseNumber))
    {
        printf("ERROR: course already exists\n");
        return;
    }

    Course course = promptForCourse();
    createCourse(courseNumber, course);
}

void update()
{
    int courseNumber = promptForCourseNumber();
    if (getCourseExists(courseNumber))
    {
        int newCourseNumber = promptForCourseNumber();
        Course updatedCourse = promptForCourse();
        Course oldCourse = getCourse(courseNumber);

        if (strlen(updatedCourse.course_Name) != 0)
        {
            strcpy(oldCourse.course_Name, updatedCourse.course_Name);
        }

        if (strlen(updatedCourse.course_Sched) != 0)
        {
            strcpy(oldCourse.course_Sched, updatedCourse.course_Sched);
        }

        if (updatedCourse.course_Size != -1)
        {
            oldCourse.course_Size = updatedCourse.course_Size;
        }

        if (updatedCourse.course_Hours != -1)
        {
            oldCourse.course_Hours = updatedCourse.course_Hours;
        }

        if (newCourseNumber != -1)
        {
            createCourse(newCourseNumber, oldCourse);
        }
        else
        {
            createCourse(courseNumber, oldCourse);
        }
    }
    else
    {
        printf("ERROR: course not found\n");
    }
}

void read()
{
    int courseNumber = promptForCourseNumber();
    if (getCourseExists(courseNumber))
    {
        Course course = getCourse(courseNumber);
        printf("Course number: %i\n", courseNumber);
        printf("Course name: %s\n", course.course_Name);
        printf("Scheduled days: %s\n", course.course_Sched);
        printf("Credit hours: %i\n", course.course_Hours);
        printf("Enrolled Students: %i\n", course.course_Size);
    }
    else
    {
        printf("ERROR: course not found\n");
    }
}

void delete ()
{
    int courseNumber = promptForCourseNumber();

    if (getCourseExists(courseNumber))
    {
        Course emptyCourse = getEmptyCourse();
        createCourse(courseNumber, emptyCourse);
    }
    else
    {
        printf("ERROR: course not found\n");
    }
}

// Helpers

Course getCourse(int courseNumber)
{
    FILE *courses = fopen("./courses.dat", "rb");
    fseek(courses, courseNumber * sizeof(Course), 0);
    Course course;
    int read = fread(&course, sizeof(Course), 1L, courses);
    fclose(courses);

    return course;
}

int getCourseExists(int courseNumber)
{
    Course course = getCourse(courseNumber);
    if (strlen(course.course_Name) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void createCourse(int courseNumber, Course course)
{
    FILE *courses = fopen("./courses.dat", "wb");

    fseek(courses, courseNumber * sizeof(Course), 0);

    long recordsWritten = fwrite(&course, sizeof(Course), 1L, courses);

    fclose(courses);
}

Course promptForCourse()
{
    Course course;
    printf("Enter a CS course name:\n");
    gets(course.course_Name);

    printf("Enter a CS course schedule:\n");
    gets(course.course_Sched);

    printf("Enter a CS course credit hours:\n");
    char courseHoursStr[10];
    gets(courseHoursStr);
    if (strlen(courseHoursStr) == 0)
    {
        course.course_Hours = -1;
    }
    else
    {
        sscanf(courseHoursStr, "%i", &course.course_Hours);
    }

    printf("Enter a CS course enrollment:\n");
    char courseSizeStr[10];
    gets(courseSizeStr);
    if (strlen(courseSizeStr) == 0)
    {
        course.course_Size = -1;
    }
    else
    {
        sscanf(courseSizeStr, "%i", &course.course_Size);
    }

    return course;
}

int promptForCourseNumber()
{
    printf("Enter a course number:\n");
    char courseNumberStr[4];
    gets(courseNumberStr);
    if (strlen(courseNumberStr) == 0)
    {
        return -1;
    }
    int courseNumber;
    sscanf(courseNumberStr, "%i", &courseNumber);
    return courseNumber;
}

void printCourse(Course course)
{
    printf("Course name:   '%s'\n", course.course_Name);
    printf("Course sched:  '%s'\n", course.course_Sched);
    printf("Course hours:  '%i'\n", course.course_Hours);
    printf("Course size:   '%i'\n", course.course_Size);
}

void printCourseNumber(int courseNumber)
{
    printf("Course number: '%i'\n", courseNumber);
}

Course getEmptyCourse()
{
    Course course;
    strcpy(course.course_Name, "");
    strcpy(course.course_Sched, "");
    course.course_Hours = -1;
    course.course_Size = -1;
    return course;
}