/*
Student Record Management System
--------------------------------
A menu-driven C program to manage student records in the terminal.
Features:
- Add, view, search, delete students
- Save/load records to/from file
- Input validation
- Modular code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define FILENAME "students.txt"

typedef struct
{
    int roll;
    char name[NAME_LEN];
    int age;
    float marks;
    char address[100];
    char email_id[100];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
int findStudentIndex(int roll);
int isValidAge(int age);
int isValidMarks(float marks);
void clearInputBuffer();

int main()
{
    int choice;
    loadFromFile();
    while (1)
    {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Delete Student\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            saveToFile();
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("Cannot add more students. Maximum reached.\n");
        return;
    }
    Student s;
    printf("Enter roll number: ");
    if (scanf("%d", &s.roll) != 1)
    {
        printf("Invalid roll number!\n");
        clearInputBuffer();
        return;
    }
    if (findStudentIndex(s.roll) != -1)
    {
        printf("Roll number already exists!\n");
        return;
    }
    printf("Enter name (max %d chars): ", NAME_LEN - 1);
    clearInputBuffer();
    fgets(s.name, NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    printf("Enter address (max 99 chars): ");
    fgets(s.address, 100, stdin);
    s.address[strcspn(s.address, "\n")] = '\0';
    printf("Enter email ID (max 99 chars): ");
    fgets(s.email_id, 100, stdin);
    s.email_id[strcspn(s.email_id, "\n")] = '\0';
    printf("Enter age (5-100): ");
    if (scanf("%d", &s.age) != 1 || !isValidAge(s.age))
    {
        printf("Invalid age!\n");
        clearInputBuffer();
        return;
    }
    printf("Enter marks (0-100): ");
    if (scanf("%f", &s.marks) != 1 || !isValidMarks(s.marks))
    {
        printf("Invalid marks!\n");
        clearInputBuffer();
        return;
    }
    students[studentCount++] = s;
    printf("Student added successfully!\n");
}

void viewStudents()
{
    if (studentCount == 0)
    {
        printf("No students to display.\n");
        return;
    }
    printf("\n%-10s %-50s %-5s %-6s %-30s %-30s\n", "Roll", "Name", "Age", "Marks", "Address", "Email ID");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++)
    {
        printf("%-10d %-50s %-5d %-6.2f %-30s %-30s\n", students[i].roll, students[i].name, students[i].age, students[i].marks, students[i].address, students[i].email_id);
    }
}

void searchStudent()
{
    int roll;
    printf("Enter roll number to search: ");
    if (scanf("%d", &roll) != 1)
    {
        printf("Invalid roll number!\n");
        clearInputBuffer();
        return;
    }
    int idx = findStudentIndex(roll);
    if (idx == -1)
    {
        printf("Student not found!\n");
    }
    else
    {
        printf("\nStudent found:\n");
        printf("Roll: %d\nName: %s\nAddress: %s\nEmail ID: %s\nAge: %d\nMarks: %.2f\n", students[idx].roll, students[idx].name, students[idx].address, students[idx].email_id, students[idx].age, students[idx].marks);
    }
}

void deleteStudent()
{
    int roll;
    printf("Enter roll number to delete: ");
    if (scanf("%d", &roll) != 1)
    {
        printf("Invalid roll number!\n");
        clearInputBuffer();
        return;
    }
    int idx = findStudentIndex(roll);
    if (idx == -1)
    {
        printf("Student not found!\n");
        return;
    }
    for (int i = idx; i < studentCount - 1; i++)
    {
        students[i] = students[i + 1];
    }
    studentCount--;
    printf("Student deleted successfully!\n");
}

void saveToFile()
{
    FILE *fp = fopen(FILENAME, "w");
    if (!fp)
    {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        fprintf(fp, "%d|%s|%s|%s|%d|%.2f\n", students[i].roll, students[i].name, students[i].address, students[i].email_id, students[i].age, students[i].marks);
    }
    fclose(fp);
    printf("Data saved to %s successfully!\n", FILENAME);
}

void loadFromFile()
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        printf("No data file found. Starting fresh.\n");
        return;
    }
    studentCount = 0;
    char line[512];
    while (fgets(line, sizeof(line), fp))
    {
        Student s;
        char *token = strtok(line, "|");
        if (!token)
            continue;
        s.roll = atoi(token);
        token = strtok(NULL, "|");
        if (!token)
            continue;
        strncpy(s.name, token, NAME_LEN);
        s.name[NAME_LEN - 1] = '\0';
        token = strtok(NULL, "|");
        if (!token)
            continue;
        strncpy(s.address, token, 100);
        s.address[99] = '\0';
        token = strtok(NULL, "|");
        if (!token)
            continue;
        strncpy(s.email_id, token, 100);
        s.email_id[99] = '\0';
        token = strtok(NULL, "|");
        if (!token)
            continue;
        s.age = atoi(token);
        token = strtok(NULL, "|");
        if (!token)
            continue;
        s.marks = atof(token);
        if (findStudentIndex(s.roll) == -1 && studentCount < MAX_STUDENTS && isValidAge(s.age) && isValidMarks(s.marks))
        {
            students[studentCount++] = s;
        }
    }
    fclose(fp);
    printf("Data loaded from %s. %d records found.\n", FILENAME, studentCount);
}

int findStudentIndex(int roll)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].roll == roll)
            return i;
    }
    return -1;
}

int isValidAge(int age)
{
    return age >= 5 && age <= 100;
}

int isValidMarks(float marks)
{
    return marks >= 0.0f && marks <= 100.0f;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/*
Sample Test Data (students.txt):
1|Alice Smith|123 Main St|alice@example.com|20|88.5
2|Bob Johnson|456 Oak Ave|bob.johnson@example.com|22|76.0
3|Charlie Lee|789 Pine Rd|charlie.lee@example.com|19|92.3

Sample Program Output:
===== Student Record Management System =====
1. Add Student
2. View All Students
3. Search Student by Roll Number
4. Delete Student
5. Save to File
6. Load from File
7. Exit
Enter your choice: 2

Roll       Name                                               Age   Marks  Address                       Email ID
-----------------------------------------------------------------------------------------------------------------------------
1          Alice Smith                                        20    88.50 123 Main St                   alice@example.com
2          Bob Johnson                                        22    76.00 456 Oak Ave                   bob.johnson@example.com
3          Charlie Lee                                        19    92.30 789 Pine Rd                   charlie.lee@example.com
*/
