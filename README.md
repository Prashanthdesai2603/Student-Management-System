Student Record Management System in C
Project Description
A terminal-based student record management system that allows users to perform CRUD (Create, Read, Update, Delete) operations on student records.

Features:-
Add new student records
View all student records in tabular format
Search for students by roll number
Delete student records
Automatic data persistence using file storage
Input validation for age and marks
Support for up to 100 students

Technical Requirements:-
C compiler (GCC recommended)
Text editor or IDE
Windows/Linux/MacOS operating system

How to Compile and Run:-

Windows# Student-Management-System
gcc student_record_management.c -o student_management.exe
./student_management.exe

Data Structure
Each student record contains:

Roll Number (unique identifier)
Name (up to 50 characters)
Address (up to 100 characters)
Email ID (up to 100 characters)
Age (5-100 years)
Marks (0-100)

File Storage:-
Records are stored in students.txt
Data format: roll|name|address|email|age|marks
Records are automatically loaded on startup
Changes are saved when exiting or using the save option

Menu Options:-
Add Student
View All Students
Search Student
Delete Student
Save to File
Load from File
Exit

Input Validation:-
Age must be between 5-100
Marks must be between 0-100
Roll numbers must be unique
Buffer overflow protection for strings

Error Handling:-
File I/O error detection
Invalid input handling
Duplicate roll number checking
Maximum capacity checking

Contributing:-
Feel free to fork and submit pull requests for improvements.

License:-
This project is open source and available under the MIT License.
